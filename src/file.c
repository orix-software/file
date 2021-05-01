#include <stdio.h>
#include <string.h>
#include <peekpoke.h>
#include "version.h"

#define SIZE_HEADER_TO_READ 44

unsigned char chars[SIZE_HEADER_TO_READ];

void version() {
  printf("file %s\n",VERSION);
}

void script_file() {
  printf("Script file\n");  
  return;
}

void tap_file() {
  printf("TAP file\n"); 
  printf("Starting adress : $%02hhX%02hhX\n",chars[10],chars[11]);
  printf("End of loading adress : $%02hhX%02hhX\n",chars[8],chars[9]);
  return;
}

void raw_file() {
  printf("Raw file\n");
  return;
}

void lz77_file() {
  printf("LZ77 file\n");
  return;
}

void wav_file() {
  unsigned int temp;
  printf("WAV file\n");
  printf("Format : ");
  printf("FileTypeBlocID : %c%c%c%c\n",chars[0],chars[1],chars[2],chars[3]);
  printf("FileSize not displayed because cc65 does not allow 32 bits\n");
  //printf("FileSize : %u\n",chars[4]+chars[5]*256+chars[6]*512++chars[7]*512*256); declare long
  printf("FileFormatID : %c%c%c%c\n",chars[8],chars[9],chars[10],chars[11]);
  printf("Audio format : \n");
  printf(" FormatBlocID : %c%c%c%c\n",chars[12],chars[13],chars[14],chars[15]);
  printf(" BlocZize : %u\n",chars[16]+chars[17]*256);
  printf(" AudioFormat :");
  temp=chars[18]+chars[19]*256;
  switch(temp) {
   case 1  :
      printf(" PCM \n");
      break;
   default :
      printf(" Unknown %d\n",temp);
  }  
  
  temp=chars[20]+chars[21]*256;
  printf(" Nbrchannel :");
  switch(temp) {
   case 1  :
      printf(" mono \n");
      break;
   case 2  :
      printf(" stereo \n");
      break;
   case 3  :
      printf(" left, right et center \n");
      break;      
   case 4  :
      printf(" left front, right front, back left, back right \n");
      break;
   case 5  :
      printf(" left, center, right, surround (ambiant) \n");
      break;
   case 6  :
      printf(" left center, left, centee, right center, right, surround (ambiant) \n");
      break;          
   default :
      printf(" Unknown \n");
  }
  printf(" Frequency : must be compute  \n"); // 22, 23,24,25
  printf(" BytePerSec :  must be compute\n"); // 26,27,28,29
  printf(" BytePerBloc : %d\n",chars[30]+chars[31]*256);
  printf(" BitsPerSample : %d\n",chars[32]+chars[33]*256);
  return;
  
    /*
  [Bloc de déclaration d'un fichier au format WAVE]
   FileTypeBlocID  (4 octets) : Constante «RIFF»  (0x52,0x49,0x46,0x46)
   FileSize        (4 octets) : Taille du fichier moins 8 octets
   FileFormatID    (4 octets) : Format = «WAVE»  (0x57,0x41,0x56,0x45)

[Bloc décrivant le format audio]
   FormatBlocID    (4 octets) : Identifiant «fmt »  (0x66,0x6D, 0x74,0x20)
   BlocSize        (4 octets) : Nombre d'octets du bloc - 16  (0x10)

   AudioFormat     (2 octets) : Format du stockage dans le fichier (1: PCM, ...)
   NbrCanaux       (2 octets) : Nombre de canaux (de 1 à 6, cf. ci-dessous)
   Frequence       (4 octets) : Fréquence d'échantillonnage (en hertz) [Valeurs standardisées : 11 025, 22 050, 44 100 et éventuellement 48 000 et 96 000]
   BytePerSec      (4 octets) : Nombre d'octets à lire par seconde (c.-à-d., Frequence * BytePerBloc).
   BytePerBloc     (2 octets) : Nombre d'octets par bloc d'échantillonnage (c.-à-d., tous canaux confondus : NbrCanaux * BitsPerSample/8).
   BitsPerSample   (2 octets) : Nombre de bits utilisés pour le codage de chaque échantillon (8, 16, 24)

[Bloc des données]
   DataBlocID      (4 octets) : Constante «data»  (0x64,0x61,0x74,0x61)
   DataSize        (4 octets) : Nombre d'octets des données (c.-à-d. "Data[]", c.-à-d. taille_du_fichier - taille_de_l'entête  (qui fait 44 octets normalement).
   DATAS[] : [Octets du Sample 1 du Canal 1] [Octets du Sample 1 du Canal 2] [Octets du Sample 2 du Canal 1] [Octets du Sample 2 du Canal 2]

   * Les Canaux :
      1 pour mono,
      2 pour stéréo
      3 pour gauche, droit et centre
      4 pour face gauche, face droit, arrière gauche, arrière droit
      5 pour gauche, centre, droit, surround (ambiant)
      6 pour centre gauche, gauche, centre, centre droit, droit, surround (ambiant)

NOTES IMPORTANTES :  Les octets des mots sont stockés sous la forme  (c.-à-d., en "little endian")
[87654321][16..9][24..17] [8..1][16..9][24..17] [...
*/
}



void vhi_file() {
  printf("VHI file\n");
  printf("Format : ");
  if (chars[3]==0)
    printf("Raw\n");
  else
    printf("Unknown\n");
  printf("Number of frames : %u\n",chars[4]+chars[5]*256);
  printf("Size of the video : %d bytes per frames\n",chars[6]+chars[7]*256);
  return;
}

#define SEDORIC_FILE  1
#define STRATSED_FILE 2
#define FTDOS_FILE    3



void orix_file() {
  if (chars[2]=='o' && chars[3]=='r' && chars[4]=='i')   {
    printf("Orix File\n");
    printf("CPU Type : ");
    if (chars[6]==0)
      printf("6502\n");
    else if  (chars[6]==1)
      printf("65C02\n");
    else if  (chars[6]==2)
      printf("65C816\n");    
    else {
      printf("Unknown CPU type\n.Orix won't start this binary\n");
      return;
  }
  // Version 1
  if (chars[5]==1) {
    printf("Loading adress : $%02hhX%02hhX\n",chars[15],chars[14]);
    printf("End of loading adress : $%02hhX%02hhX\n",chars[17],chars[16]);
    printf("Starting adress : $%02hhX%02hhX\n",chars[19],chars[18]);
    printf("Size : %u bytes\n",(chars[16]+chars[17]*256)-(chars[14]+chars[15]*256));
    return;
  }
  
  if (chars[5]==2) {
    printf("Format version 2 : reloc binary\n");
    printf("Map size : $%02hhX%02hhX\n",chars[19],chars[18]);
    return;
  }
  
  printf("Unknown format");
  return;
  }
 printf("Unknown format");
return;
}

void usage()
{
  printf("usage:\n");
  printf("file FILENAME\n");
  printf("file -v|--version : displays version\n");
  printf("file -h|--help : displays help\n");
  return;
}
    
int main(int argc,char *argv[])
{
  FILE *fp;
  int nb;
  unsigned char val;


  if (argc==2 && (strcmp(argv[1],"--version")==0 || strcmp(argv[1],"-v")==0))
  {

    version();
    return 0;
  }
 
  if (argc==2 && (strcmp(argv[1],"--help")==0 || strcmp(argv[1],"-h")==0))
  {
    usage();
    return 0;
  } 
 
  if (argc!=2)
  {
    usage();
    return(1);
  }
/*
  for (nb=0;nb<10;nb++)
  {
    val=PEEK(0x0590+nb);
    printf("%c",val);
  }
  */
  fp=fopen(argv[1],"r");
  if (fp==NULL)
  {
    printf("Can't open %s\n",argv[1]);
    /*
    for (nb=0;nb<10;nb++)
    {
      val=PEEK(0x0590+nb);
      printf("%c",val);
    } */   
    return (1);
  }   
        
  nb=fread(chars,SIZE_HEADER_TO_READ,1,fp);

  switch (chars[0])
  {
    case '#':
    if (chars[1]=='!')
      script_file();
      break;
    case 0x16:                
      if (chars[1]==0x16 && chars[2]==0x16  && chars[3]==0x24)
        tap_file();
        break;
    case 0x1f:                
      if (chars[1]==0x8b)
         printf("gzip format\n");
      break;
        
    case 1:
      if (chars[1]==0)
      {
        orix_file();
      }
      break;
    case 'L':
      if (chars[1]=='Z')
        lz77_file();
        break;
    case 'R':
      if (chars[1]=='I' && chars[2]=='F' && chars[3]=='F' )
        wav_file();
        break;     
    case 'V':
      if (chars[1]=='H' && chars[2]=='I')
        vhi_file();
        break;        
        
    default:
      raw_file(); 
   }
   
   fclose(fp);

  return 0;
}