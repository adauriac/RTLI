import numpy as np

def rfim_1d(hs, Js):
    """
    les deux tableaux doivent etre de taille L.
    J[i] = lien entre spin_{i} et spin_{i+1}
    Les conditions sont périodiques mais si Js[-1]==0 on utilise la fonction speciale du cas open.
    retourne le tableau des spins, la valeur du fondamental et la degenerescnce (boolean)
    """
    if Js[-1]==0:
        # print('OPEN')
        return rfim_1dOpen(hs, Js)
    else:
        # print('PERIODIC')
        return rfim_1d_periodic(hs, Js)
  
def rfim_1dOpen(hs, Js):
    """
    Ground state of a 1D ferromagnetic RFIM with open boundaries.
    Hamiltonian:
        H = - sum_i J_i s_i s_{i+1} - sum_i h_i s_i
    Parameters
    ----------
    hs : np.array         Random fields h_i, length N.
    Js : np.array         Coupling  array [J_0, ..., J_{N-1}].

    Returns
    -------
    spins : np.array
        One ground-state configuration, values +/-1.
    E0 : float
        Ground-state energy.
    degenerate : bool
        True if there is more than one ground-state configuration.
    """

    hs = np.asarray(hs, dtype=float)
    L = len(hs)
    if L == 0:
        raise ValueError("hs ne doit pas être vide")
    # Couplings
    if len(Js) != L:
        raise ValueError("Js doit avoir L-1 éléments")
    # Eplus / Eminus au site précédent
    Eplus = -hs[0]
    Eminus = +hs[0]
    # Pour reconstruire une configuration fondamentale
    prev_plus = np.zeros(L, dtype=np.int8)
    prev_minus = np.zeros(L, dtype=np.int8)
    # Nombre de chemins fondamentaux arrivant dans chaque état.
    # On limite à 2 : on veut seulement savoir s'il y a dégénérescence.
    nplus = 1
    nminus = 1
    for i in range(1, L):
        J = Js[i - 1]
        # Etat s_i = +1
        a = Eplus - J
        b = Eminus + J
        Enew_plus = -hs[i] + min(a, b)
        if np.isclose(a, b):
            prev_plus[i] = 2       # les deux possibilités
            nnew_plus = min(2, nplus + nminus)
        elif a < b:
            prev_plus[i] = +1
            nnew_plus = nplus
        else:
            prev_plus[i] = -1
            nnew_plus = nminus
        # Etat s_i = -1
        a = Eminus - J
        b = Eplus + J
        Enew_minus = +hs[i] + min(a, b)
        if np.isclose(a, b):
            prev_minus[i] = 2
            nnew_minus = min(2, nplus + nminus)
        elif a < b:
            prev_minus[i] = -1
            nnew_minus = nminus
        else:
            prev_minus[i] = +1
            nnew_minus = nplus
        Eplus = Enew_plus
        Eminus = Enew_minus
        nplus = nnew_plus
        nminus = nnew_minus
    # Choix du dernier spin
    if np.isclose(Eplus, Eminus):
        E0 = Eplus
        degenerate = True
        # On choisit arbitrairement +1 comme configuration retournée
        spin = +1
    elif Eplus < Eminus:
        E0 = Eplus
        degenerate = (nplus > 1)
        spin = +1
    else:
        E0 = Eminus
        degenerate = (nminus > 1)
        spin = -1
    # Reconstruction de la configuration
    spins = np.empty(L, dtype=np.int8)
    spins[-1] = spin
    for i in range(L - 1, 0, -1):
        if spins[i] == +1:
            p = prev_plus[i]
        else:
            p = prev_minus[i]
        # En cas d'égalité, on avait mis p = 2.
        # On choisit arbitrairement +1.
        if p == 2:
            p = +1 if spins[i] == +1 else -1
        spins[i - 1] = p
    return spins, E0, degenerate
# FIN def rfim_1d_open(hs, Js):
#################################################################

def rfim_1d_periodic(hs, Js):
    """
    Fondamental du modèle RFIM 1D avec conditions périodiques.
    H = - sum_i J_i s_i s_{i+1} - sum_i h_i s_i    avec s_L = s_0.
    Parameters
    ----------
    hs : array
        Champs h_i, longueur L.
    Js : float ou array
        Couplages.
        Si scalaire : même J pour toutes les liaisons.
        Sinon : tableau de longueur L, avec
                Js[i] entre s_i et s_(i+1),
                et Js[L-1] entre s_(L-1) et s_0.
    Returns
    -------
    spins : array
        Une configuration fondamentale.
    E0 : float
        Énergie fondamentale.
    degenerate : bool
        True si le fondamental est dégénéré.
    """

    hs = np.asarray(hs)
    L = len(hs)

    if L < 2:
        raise ValueError("Il faut au moins L = 2 spins")

    # Couplages
    if len(Js) != L:
        raise ValueError("Pour des conditions périodiques, "
                             "Js doit avoir L éléments")
    # --------------------------------------------------
    # Résout le problème en imposant s_0 = first_spin
    # --------------------------------------------------
    def solve(first_spin):
        # Énergie du premier spin
        if first_spin == +1:
            Eplus = -hs[0]
            Eminus = np.inf
        else:
            Eplus = np.inf
            Eminus = +hs[0]
        # Nombre de chemins minimaux
        nplus = 1 if first_spin == +1 else 0
        nminus = 1 if first_spin == -1 else 0
        # Prédécesseurs
        prev_plus = np.zeros(L, dtype=np.int8)
        prev_minus = np.zeros(L, dtype=np.int8)
        # Dynamique sur les L-1 premières liaisons
        for i in range(1, L):
            J = Js[i - 1]
            # s_i = +1
            a = Eplus - J
            b = Eminus + J
            if a < b:
                Enew_plus = -hs[i] + a
                prev_plus[i] = +1
                nnew_plus = nplus
            elif b < a:
                Enew_plus = -hs[i] + b
                prev_plus[i] = -1
                nnew_plus = nminus
            else:
                Enew_plus = -hs[i] + a
                prev_plus[i] = 2
                nnew_plus = min(2, nplus + nminus)
            # s_i = -1
            a = Eminus - J
            b = Eplus + J
            if a < b:
                Enew_minus = +hs[i] + a
                prev_minus[i] = -1
                nnew_minus = nminus
            elif b < a:
                Enew_minus = +hs[i] + b
                prev_minus[i] = +1
                nnew_minus = nplus
            else:
                Enew_minus = +hs[i] + a
                prev_minus[i] = 2
                nnew_minus = min(2, nplus + nminus)
            Eplus = Enew_plus
            Eminus = Enew_minus
            nplus = nnew_plus
            nminus = nnew_minus
        # --------------------------------------------------
        # Ajouter le couplage périodique entre s_(L-1) et s_0
        # --------------------------------------------------
        Eplus_periodic = Eplus - Js[L - 1] * (+1) * first_spin
        Eminus_periodic = Eminus - Js[L - 1] * (-1) * first_spin
        # Choisir le dernier spin
        if Eplus_periodic < Eminus_periodic:
            E = Eplus_periodic
            last_spin = +1
            deg = (nplus >= 2)
        elif Eminus_periodic < Eplus_periodic:
            E = Eminus_periodic
            last_spin = -1
            deg = (nminus >= 2)
        else:
            E = Eplus_periodic
            last_spin = +1
            deg = True
        # Reconstruction
        spins = np.empty(L, dtype=np.int8)
        spins[-1] = last_spin
        for i in range(L - 1, 0, -1):
            if spins[i] == +1:
                p = prev_plus[i]
            else:
                p = prev_minus[i]
            if p == 2:
                # choix arbitraire parmi les deux possibilités
                if spins[i] == +1:
                    p = +1
                else:
                    p = -1
            spins[i - 1] = p
        return spins, E, deg
    # FIN solve
    # --------------------------------------------------
    # Deux possibilités pour le premier spin
    # --------------------------------------------------
    spins_plus, E_plus, deg_plus = solve(+1)
    spins_minus, E_minus, deg_minus = solve(-1)
    # Comparaison des deux secteurs
    if E_plus < E_minus:
        return spins_plus, E_plus, deg_plus
    elif E_minus < E_plus:
        return spins_minus, E_minus, deg_minus
    else:
        # Les deux configurations ont des premiers spins différents :
        # elles sont donc nécessairement différentes.
        return spins_plus, E_plus, True
# FIN def rfim_1d(hs, Js):
#################################################################

import time,sys
if len(sys.argv)==2:
    seed=12345
    rng = np.random.default_rng(seed)
    L = int(sys.argv[1])
    hs = rng.uniform(-1,1,L)
    Js = rng.uniform(0,1,L)
else:
    lines= open("dataTest").readlines()
    hs=[]
    Js=[]
    for line in lines:
        ls = line.split()
        hs.append(float(ls[0]))
        Js.append(float(ls[1]))
    hs= np.array(hs)
    Js= np.array(Js)
print(f"{hs=}")
print(f"{Js=}")
t0 = time.perf_counter()
Gs,E0,deg = rfim_1d(hs,Js)
print(f"{Gs=}")
t1 = time.perf_counter()
print(f"{E0=} {(t1 - t0) * 1000} ms")
