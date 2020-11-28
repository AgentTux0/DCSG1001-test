/**
 * Infrastruktur-øvelse - Et program som tester kunnskaper om kommandoer
 * 
 * Programmet leser spørsmål fra en fil med følgende struktur:
 *      <spørsmål 1>
 *      <svar 1>
 *      ...
 *      <spørsmål N>
 *      <svar N>
 *  Brukeren stilles spørsmål om egnet kommando og svaret til brukeren
 *  sammenlignes med fasiten. Det telles opp poeng og ved slutt får brukeren
 *  vite total poengsum og prosentvis korrekte svar.
 *
 *  @file infratest.c
 *  @author Alexander P. Roaas
 */

// INCLUDES //
#include <stdio.h>  // FILE*, printf, fgets
#include <stdlib.h> // malloc, sizeof, free
#include <string.h> // strlen

// CONSTER //
#define MAXSPM 100
#define STRLEN 200

// STRUCTER //
struct Spm {
    char* spm;
    char* svar;
};

// FUNKSJONSPROTOTYPER //
void lesDataFraFil();
void lesSpmFraFil(FILE* inn, struct Spm* spm, const char s[]);

void stillSpm(const struct Spm* spm);

int  finnProsent();


// GLOBALE VARIABLE //
int gAntallSpm = 0;
int gKorrekteSvar = 0;
struct Spm* gSpm[MAXSPM];

int main() {
    int prosent;
    lesDataFraFil();

    for (int i = 0; i < gAntallSpm; i++) {
        printf("Spørsmål nr. %i\n", i+1);
        stillSpm(gSpm[i]); 
        if (!(gKorrekteSvar % 10) && gKorrekteSvar > 0)
            printf("\n\t%i riktige svar!\n\n", gKorrekteSvar);
    }
    prosent = finnProsent();
    printf("\n\t|| Alle spørsmål er nå besvart.\n\t||Du fikk %i riktige av %i spørsmål (%i\%)\n", gKorrekteSvar, gAntallSpm, prosent);
    switch (prosent/10) {
        case 0:  printf("\t||Var du i timene?\n");                     break;
        case 1:  printf("\t||Du må lese myyyyye kompis\n");            break;
        case 2:  printf("\t||Du må lese myyye kompis\n");              break;
        case 3:  printf("\t||Du må lese mye kompis\n");                break;
        case 4:  printf("\t||Det er nok til en ståkarakter (ish)\n");  break;
        case 5:  printf("\t||Halvparten riktig, stå på!\n");           break;
        case 6:  printf("\t||Flere riktige enn gale svar\n");          break;
        case 7:  printf("\t||Nå begynner det å se lyst ut!\n");        break;
        case 8:  printf("\t||Dette begynner å bli bra!\n");            break;
        case 9:  printf("\t||Nå er du i A-land!! Dritbra!\n");         break;
        case 10: printf("\t||Hatten av, du alt riktig!!!\n");         break;
    }
   
    return 0;
}

/**
 * Leser all data fra en fil
 *
 * @see lesSpmFraFil(...)
 */
void lesDataFraFil() {
    FILE* inn = fopen("spm.dat", "r");
    char  buffer[STRLEN];
    int   i = 0;

    if (inn) { // Dersom filåpning var vellykket
        printf("\tLeser inn fra \"spm.dat\"");
        fgets(buffer, STRLEN, inn); buffer[strlen(buffer)-1] = '\0';
        while (!feof(inn)) { // For hvert spørsmål til slutten av filen er nådd
            gSpm[i] = (struct Spm*) malloc(sizeof(struct Spm)); 
            lesSpmFraFil(inn, gSpm[i++], buffer);
            gAntallSpm++;
            fgets(buffer, STRLEN, inn); buffer[strlen(buffer)-1] = '\0';
        }
        fclose(inn);
        printf("\r\tInnlesning fullført!     \n\tLa til %i spørsmål\n\n", gAntallSpm);
    } else  // Dersom filåpning mislyktes
        printf("\tKunne ikke åpne \"spm.dat\"\n");
}

/**
 * Leser spørsmål og svar fra fil til datamedlemmene til det aktuelle spørsmålet
 *
 * @param inn   - Filen det skal leses fra
 * @param spm   - Peker til structen som skal oppdateres
 * @param   s   - Teksten til spørsmålet
 */
void lesSpmFraFil(FILE* inn, struct Spm* spm,  const char s[]) {
    char buffer[STRLEN];

    spm->spm = (char*) malloc((strlen(s) + 1)  * sizeof(char));
    strcpy(spm->spm, s);

    fgets(buffer, STRLEN, inn); buffer[strlen(buffer)-1] = '\0';
    spm->svar = (char*) malloc((strlen(buffer) + 1) * sizeof(char));
    strcpy(spm->svar, buffer);
}


/**
 * Stiller spørsmålet, tar imot svaret og sjekker om det er riktig eller ei
 *
 * @param spm   - Structen til det aktuelle spørsmålet
 */
void stillSpm(const struct Spm* spm) {
    char svar[STRLEN];
    printf("\t%s\n\tSvar: ", spm->spm);
    fgets(svar, STRLEN, stdin); svar[strlen(svar)-1] = '\0';
    
    if (!strcmp(svar, spm->svar)) {
        printf("\tKorrekt!\n\n");
        gKorrekteSvar++;
    }
    else
        printf("\n\tFeil, rett svar er:\n\t%s\n\n", spm->svar);
}

/**
 * Regner ut prosenten av riktige svar
 *
 * @return int-verdi for prosent
 */
int finnProsent() {
    return ((float) gKorrekteSvar/gAntallSpm) * 100;
}
