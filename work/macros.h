#include <stdlib.h>
#include <unistd.h>
#include <sys/times.h> 

// **********************************************************************
//                            MACROS
// **********************************************************************
#ifndef _PRINTF
#define _PRINTF(v,...) if (verbose>=v) printf(__VA_ARGS__) /* Ok. */
#endif

#ifndef _ALLOUE
#define _ALLOUE(nom,size,type){\
	nom = (type *)malloc((size)*sizeof(type));\
	if (nom==0) {printf("Not enough memory for %s\n",#nom);exit(0);}}
/* _ALLOUE(T1,n*n,double) */
#endif

#ifndef _REALLOUE
#define _REALLOUE(nom,size,type){\
        nom = (type *)realloc((void *)nom,(size)*sizeof(type));\
        if (nom==0) {printf("Can't realloc %s\n",#nom);exit(0);}}
/* _REALLOUE(T1,n*n,double) */
#endif

#ifndef _CALLOUE
#define _CALLOUE(nom,size,type){\
  nom = (type *)calloc(size,sizeof(type));                             \
	if (nom==NULL) {printf("Not enough memory for %s\n",#nom);exit(0);}}
/* _ALLOUE(T1,n*n,double) */
#endif

#ifndef _OUVREFILE
#define _OUVREFILE(nom,ft,mode) {\
	ft = fopen(nom,mode);\
	if (ft==0) {printf("Can't open %s",nom);exit(0);}}
#endif

#ifndef _LONGSTAUX
#define _LONGSTAUX 8192
#endif

#ifndef _Q
#define _Q(nom,format,comment)                                  \
  if ((i==na)&&(j==0))                                          \
    {                                                           \
      char noml2[_LONGSTAUX];                                   \
      sprintf(noml,"%s=%s ",#nom,format);                       \
      sprintf(noml2,noml,nom);                                  \
    }                                                           \
  else if (j==1)                                                \
    {                                                           \
      if (!ok)                                                  \
        {                                                       \
          sprintf(noml,"%s=%s%s\n",#nom,format,comment);        \
          printf(noml,nom);}                                    \
    }                                                           \
  else                                                          \
    {                                                           \
      strcpy(noml,#nom);                                        \
      strcat(noml,"=");                                         \
      if (strncmp(st,noml,strlen(noml))==0)                     \
        {                                                       \
          ok = (sscanf(&st[strlen(noml)],format,&nom)==1);      \
        }                                                       \
    }
#endif

#ifndef _QS
#define _QS(nom,format,comment)                                 \
  if ((i==na)&&(j==0))                                          \
    {                                                           \
      char noml2[_LONGSTAUX];                                          \
      sprintf(noml,"%s=%s ",#nom,format);                       \
      sprintf(noml2,noml,nom);                                  \
    }                                                           \
  else if (j==1)                                                \
    {                                                           \
      if (!ok)                                                  \
        {                                                       \
          sprintf(noml,"%s=%s%s\n",#nom,format,comment);        \
          printf(noml,nom);					\
	}							\
    }                                                           \
  else                                                          \
    {                                                           \
      strcpy(noml,#nom);                                        \
      strcat(noml,"=");                                         \
      if (strncmp(st,noml,strlen(noml))==0)                     \
        {                                                       \
          ok = (sscanf(&st[strlen(noml)],format,nom)==1);       \
        }                                                       \
    }
#endif

#ifndef _QU
#define _QU(nom,format,comment)                                 \
  if ((i==na)&&(j==0))                                          \
    {                                                           \
      char noml2[_LONGSTAUX];                                   \
      sprintf(noml,"%s=%s ",#nom,format);                       \
      sprintf(noml2,noml,nom);                                  \
      redo += string(noml2);                                    \
    }                                                           \
  else if (j==1)                                                \
    {                                                           \
      if (!ok)                                                  \
        {                                                       \
          sprintf(noml,"%s=%s%s\n",#nom,format,comment);        \
          printf(noml,nom);}                                    \
    }                                                           \
  else                                                          \
    {                                                           \
      strcpy(noml,#nom);                                        \
      strcat(noml,"=");                                         \
      if (strncmp(st,noml,strlen(noml))==0)                     \
        {                                                       \
          ok = (sscanf(&st[strlen(noml)],format,&nom)==1);      \
        }                                                       \
    }
#endif

#ifndef _QUS
#define _QUS(nom,format,comment)                                \
  if ((i==na)&&(j==0))                                          \
    {                                                           \
      char noml2[_LONGSTAUX];                                          \
      sprintf(noml,"%s=%s ",#nom,format);                       \
      sprintf(noml2,noml,nom);                                  \
      redo += string(noml2);                                    \
    }                                                           \
  else if (j==1)                                                \
    {                                                           \
      if (!ok)                                                  \
        {                                                       \
          sprintf(noml,"%s=%s%s\n",#nom,format,comment);        \
          printf(noml,nom);                                     \
        }							\
    }                                                           \
  else                                                          \
    {                                                           \
      strcpy(noml,#nom);                                        \
      strcat(noml,"=");                                         \
      if (strncmp(st,noml,strlen(noml))==0)                     \
        {							\
	  if (st[strlen(noml)]==0)				\
	    {							\
	      nom[0] = 0;					\
	      ok = 1;						\
	    }							\
	  else                                                  \
	    {							\
	      ok = 1;						\
	      strcpy(nom,st+strlen(#nom)+1);			\
	    }							\
        }                                                       \
    }
#endif

#ifndef _INITQ
#define _INITQ                                          \
  string redo = string(para[0])+" ";                    \
  string cmdline = string(para[0])+" ";                 \
  string infostring = "";                               \
  {                                                     \
    char aux[256];                                      \
    char *pwd = getenv("PWD");                          \
    if (pwd==NULL)                                      \
      infostring += "# workingdir= inconnu\n";          \
    else                                                \
      infostring += "workingdir= "+string(pwd)+"\n";    \
    if (gethostname(aux,255)!=0)                        \
      strcpy(aux,"unknown\n");                          \
    infostring += "# hostname= "+string(aux) +"\n";     \
    time_t t = time(NULL);                              \
    strcpy(aux,ctime(&t));                              \
    infostring += "# date= "+string(aux);               \
    infostring.erase(infostring.size()-1);              \
  }                                                     \
  struct tms timebufbegin;                              \
  times(&timebufbegin);                                  
#endif

#ifndef _PRINT_TIMENOW // SEULEMNT si _INITQ a ete appelle
#define _PRINT_TIMENOW(ft)                                              \
  {                                                                     \
    struct tms timebufnow;                                              \
    times(&timebufnow);                                                 \
    double conversion = (double)sysconf(_SC_CLK_TCK); /* tics/secondes*/ \
    int temps  = (int)(timebufnow.tms_utime - timebufbegin.tms_utime +  \
                       timebufnow.tms_stime - timebufbegin.tms_stime);  \
    fprintf(ft,"# duree_depuis_debut= %.15lg seconde(s)\n",             \
            temps/conversion);                                          \
  }
#endif

#ifndef _ELAPSEDSEC // SEULEMNT si _INITQ a ete appelle
// double v;_ELAPSEDSEC(c);  affecte v a u nombre de sec depusi le debut
#define _ELAPSEDSEC(v)                                                  \
  {                                                                     \
    struct tms timebufnow;                                              \
    times(&timebufnow);                                                 \
    double conversion = (double)sysconf(_SC_CLK_TCK); /* tics/secondes*/ \
    int temps  = (int)(timebufnow.tms_utime - timebufbegin.tms_utime +  \
                       timebufnow.tms_stime - timebufbegin.tms_stime);  \
   v = temps/conversion;                                                \
  }
#endif

#ifndef _PROTO_QSORT
#define _PROTO_QSORT (int (*)(const void *, const void *))
#endif

#ifndef _STOP
#define _STOP(format, ...) {printf (format, ## __VA_ARGS__);exit(0);}
#endif

#ifndef _STOPERR
#define _STOPERR(format, ...) {fprintf (stderr,format, ## __VA_ARGS__);exit(0);}
#endif

#ifndef _WRITEINSTRING
#define _WRITEINSTRING(st,...) {char aux[2048];sprintf(aux,__VA_ARGS__);st=aux;}
#endif
#ifndef _DISPLAY_MEMINFO
#define _DISPLAY_MEMINFO {struct mallinfo mi = mallinfo();\
      printf("# %6d %6d %6d %6d %6d %6d %6d %6d %6d %6d\n",\
	     mi.arena,     /* Non-mmapped space allocated (bytes) */	\
	     mi.ordblks,   /* Number of free chunks */\
	     mi.smblks,    /* Number of free fastbin blocks */\
	     mi.hblks,     /* Number of mmapped regions */\
	     mi.hblkhd,    /* Space allocated in mmapped regions (bytes) */\
	     mi.usmblks,   /* Maximum total allocated space (bytes) */\
	     mi.fsmblks,   /* Space in freed fastbin blocks (bytes) */\
	     mi.uordblks,  /* Total allocated space (bytes) */\
	     mi.fordblks,  /* Total free space (bytes) */\
	     mi.keepcost);  /* Top-most, releasable space (bytes) */}
#endif

#ifndef _INDEX_SITE_4
#define _INDEX_SITE_4(k1,k2,k3,k4) ((((k1)*L2 + (k2))*L3 + (k3))*L4 + (k4))
#define _UNINDEX_SITE_4(i,k1,k2,k3,k4) {int aux=i;k1=aux/L234;aux %= L234;k2=aux/L34;aux %= L34;k3=aux/L4;k4 = aux%L4;}
#endif

#ifndef _INDEX_SITE_3
#define _INDEX_SITE_3(k1,k2,k3) (((k1)*L2 + (k2))*L3 + (k3))
#define _UNINDEX_SITE_3(i,k1,k2,k3) {int aux=i;k1=aux/L23;aux %= L23;k2=aux/L3;k3 = aux%L3;}
#endif

#ifndef _INDEX_SITE_2
#define _INDEX_SITE_2(k1,k2) ((k1)*L2 + (k2))
#define _UNINDEX_SITE_2(i,k1,k2) {k1=i/L2;k2 = i%L2;}
#endif

#ifndef _DT_IN_TICS
#define _DT_IN_TICS(b1,b2) ((int)(-b1.tms_utime + b2.tms_utime-b1.tms_stime + b2.tms_stime))
#endif

#ifndef _DT_IN_SECS
#define _DT_IN_SECS(b1,b2) (((double)((-b1.tms_utime + b2.tms_utime-b1.tms_stime + b2.tms_stime)))/sysconf(_SC_CLK_TCK))
#endif

#ifndef _MIN
#define _MIN(a,b) (((a)<(b)) ? (a) : (b))
#endif

#ifndef _MAX
#define _MAX(a,b) (((a)<(b)) ? (b) : (a))
#endif

#ifndef _ABS
#define _ABS(a) (((a)<0) ? (-(a)) : (a))
#endif

#ifndef _ADD_SEED
#define _ADD_SEED {                              \
  std::ostringstream oss;                        \
  oss << seed;                                   \
  cmdline+= "seed="+oss.str()+" ";}
#endif

#ifndef _SET_SEED
#define _SET_SEED if (seed==0) {                 \
    initR1279(&seed);                            \
    std::ostringstream oss;                      \
    oss << seed;                                 \
    cmdline += "seed="+oss.str()+" ";            \
    {						 \
      int k = (int)redo.find("seed=0");		 \
      char aux[64];				 \
      sprintf(aux,"%d",(int)seed);		 \
      redo.replace(k+5,1,aux);			 \
    }						 \
  }						 \
  else						 \
    initR1279(&seed); 
#endif

#ifndef _IMPRIM_PARAM
#define _IMPRIM_PARAM(ft)  {                            \
  fprintf(ft,"# redo: %s\n",redo.c_str());              \
  fprintf(ft,"# cmdline: %s\n",cmdline.c_str());        \
  fprintf(ft,"# %s\n",infostring.c_str());}  
#endif
