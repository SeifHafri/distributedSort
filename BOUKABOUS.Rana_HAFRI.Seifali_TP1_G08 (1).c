/**TP1 ALSDD 1cpi-G08 2018/2019 realis� par :Boukabous Rana_Hafri Seif Ali**/
/**TRI PAR DISTRIBUTION**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
///Les differentes structures dont on aura besoin:

typedef struct TABMOTS
{
    char mot[16];
} TABMOTS; ///une structure enregistrement afin de creer un tableau de mots

typedef struct maillon *pointeur; ///pour la declaration directe d'un pointeur
typedef struct maillon
{
    char *val;
    struct maillon *suiv;
} maillon;

typedef struct tablist
{
    char lettre;
    maillon *deb;
    maillon *fin;
} tablist; ///une structure enregistrement modele d'un element constituant le tableau tabliste

///Modele de LLC etudi� en cour:
///****************************************** 1:
pointeur suivant(pointeur p)
{
    return p->suiv;
}
///****************************************** 2:
int longueur_llc(pointeur tete)
{
    int cpt = 0;
    pointeur p = tete;
    while (p != NULL)
    {
        cpt++;
        p = suivant(p);
    }
    return cpt;
}
///****************************************** 3:
void aff_val(maillon *p, char *valeur) { p->val = valeur; }
///****************************************** 4:
void aff_adr(maillon *p, maillon *q) { p->suiv = q; }
///****************************************** 5:
void liberer(pointeur P) { free(P); }
///****************************************** 6:
/**Allocation**/
void allouer(pointeur *nouveau)
{
    *nouveau = (maillon *)malloc(sizeof(maillon));
    (*nouveau)->suiv = NULL;
}
///******************************************* 7:
/**Recuperer la valeur d'un pointeur**/
char *valeur(pointeur p) { return p->val; }
/**Creation des procedures qu'on va utiliser**/

void color(int textcolor, int backgroundcolor); ///affichage du texte en couleurs

void inittablist(tablist *tabliste) /**Role:cette procedure nous met tout les pointeurs de debut et fin de tabliste a NIL**/

{
    int i;
    for (i = 0; i < 26; i++)
    {
        tabliste[i].deb = NULL;
        tabliste[i].fin = NULL;
    }
}

void gener_mot_aleat(int N, int m, FILE *fichier) /**Role:Generer des mots aleatoirement et les mettre dans un fichier**/
{                                                 ///(*Remarquer que cette solution n'est pas parfaite mais elle a ete con�ue afin de generer des mots qui ont un sens contenus dans le dictionnaire francais*)

    int r, i;
    char *mots[63] = {"arme", "arbre", "seif", "Nana", "hahaha", "lundi","Roi","Vie","cadeau","thon","fichier","ecole","tech","module","chat","boucle","verre","ciel","ville","destin","couleur","cher","bateau","orage","decision","changer","nous","haine","neige","dieu","jeudi", "prince", "anneau", "ancre", "branche", "berceau", "circuit", "cerner", "servir", "dancer", "dortoir", "dormir", "effacer", "frange", "freiner", "formule", "gagner", "grand", "harpie", "inertie", "jardin", "journal", "kernel", "larme", "nord", "ordre", "prude", "prise", "prune", "blond", "brune", "reste", "tendre"};
    srand(time(NULL)); ///on prend le temps comme variable pour utiliser la fonction random par la suite i.e une notion qui n'est jamais constante
    if (fichier != NULL)
    {
        for (i = 0; i < N; i++)
        {
            r = rand() % 62;          ///Ici la generation se fait uniquement par rapport au nombre de mots constants contenus dans notre tableau mots
            if (strlen(mots[r]) != m) ///Verification de la taille des mots entres
            {
                while (strlen(mots[r]) != m) ///regenerer des entiers tant que la taille trouvee n'est pas la bonne
                {
                    r = rand() % 62;
                }
            }
            if (strlen(mots[r]) == m)
            {
                fprintf(fichier, "%s\n", mots[r]); ///Ecriture dans le fichier du mot g�n�r�
            }
        }
    }
    fclose(fichier);
} ///Cette procedure nous gen�re al�atoirement des mots et les stocke dans un fichier "fichmots"

void inser_tab_mots(TABMOTS *tabmots, int N, int m) ///Role:Cette procedure insere des mots saisis par l'utilisateur dans un tableau "tabmots"
{
    int i;
    char word[16];
    ///initialisation du tableau:*****
    for (i = 0; i < N; i++)
        strcpy(tabmots[i].mot, " ");
    ///*******************************
    printf("Veuillez saisir le premier mot\n");
    for (i = 0; i < N; i++)
    {
        if (i != 0)
            printf("\nveuillez saisir le mot suivant\n");
        scanf("%s", word);
        if (strlen(word) != m)
        {
            while (strlen(word) != m) ///Boucle de verification de la taille des mots ins�r�s par l'utilisateur
            {
                printf("\nveuillez resaisir votre mot ; �a doit contenir %d lettres SVP\n", m);
                scanf("%s", word);
            }
        }
        if (strlen(word) == m)
            strcpy(tabmots[i].mot, word); ///Inserer l'element seulement dans le cas o� sa taille est �gale a 'm'
    }
}

void Insertfinliste(maillon **adr1, char *mot, maillon **adr2) /**Role:inserer des valeurs a la fin de la liste qui commence par adr1 et se finie par le pointeru adr2**/
{
    ///Le passage des pointeurs 'adr1' et 'adr2' se fait par variable alors
    maillon *p = NULL;
    if (*adr1 == NULL) ///Cas du premier element insere dans la liste
    {
        allouer(adr1); ///pour l'allocation on applique double fois l'effet du "&" d'ou son absence
        aff_val(*adr1, mot);
        aff_adr(*adr1, NULL);
        *adr2 = *adr1; ///La liste contenant un seul element sa tete= sa queue
    }
    else
    {
        allouer(&p);       ///on alloue un maillon separemment de adr1
        aff_adr(*adr2, p); ///on le lie a la fin de la liste
        aff_val(p, mot);
        aff_adr(p, NULL); ///*Dernier element ajoute*
        *adr2 = p;        /// p devient la nouvelle queue de la liste soit adr2
    }
}

void concatlistes_1(tablist *tabliste, TABMOTS *tabmots, int N) /**Role:Mettre le contenu de tabliste dans un tableau**/
{
    int i;
    TABMOTS tab[N];
    for (i = 0; i < N; i++)
    {
        strcpy(tab[i].mot, tabmots[i].mot);
    }           ///Utilisation d'un tableau de mots intermediaire
    maillon *p; ///Un pointeur qui va parcourir les maillons au fur et a mesure qu'on avance dans le tableau pour l'utilisation en cas de liste contenant plusieurs elements
    i = 0;
    int j = 0; //i pour le parcours de tabliste et j afin d'incrementer l'indice du tableau en cour de remplissage
    while (i < 26)
    {
        if (tabliste[i].deb != NULL) ///Si liste non vide
        {
            p = tabliste[i].deb;
            if (tabliste[i].deb == tabliste[i].fin) ///Cas un seul element dans la liste
            {
                strcpy(tab[j].mot, valeur(p)); ///Recuperer la valeur dans le tableau
                j++;
            }
            else
            { ///Sinon on parcours toute la liste pour recuperer ses elements dans notre tableau
                while (p != NULL)
                {
                    strcpy(tab[j].mot, valeur(p));
                    j++; ///pour remplir ensuite l'element i+1 du tableau
                    p = suivant(p);
                }
            }
        }
        i++;
    }
    for (i = 0; i < N; i++)
    {
        strcpy(tabmots[i].mot, tab[i].mot);
    } ///Les valeurs sont plac�es dans tabmots
}

void concatlistes_2(tablist *tabliste, FILE *fichier, int N) /**Role:Mettre les elments de tabliste dans un fichier**/
{
    int i = 0;
    if (fichier != NULL) ///Pour s'assurer que le fichier s'etait bien ouvert
    {
        while (i < 26)
        {
            if (tabliste[i].deb != NULL)
            {
                pointeur p = tabliste[i].deb;
                if (tabliste[i].deb == tabliste[i].fin) ///Cas un seul element
                {
                    fprintf(fichier, "%s", valeur(p)); ///insertion dans le fichier
                }
                else
                { ///Cas on a une liste a plusieurs elements
                    while (p != NULL)
                    {
                        fprintf(fichier, "%s", valeur(p));
                        p = suivant(p);
                    }
                }
            }
            i++;
        }
    }
}

void distribue_1(TABMOTS *tabmots, int N, tablist *tabliste, int k) /**Role:Mettre les mots du tableau tabmots dans tabliste**/
{
    int i, j;
    char *caract = {0};
    for (i = 0; i < N; i++)
    {
        caract = tabmots[i].mot; ///Utilisation de caract comme chaine de caracteres intermediaire lors du traitement
        for (j = 0; j < 26; j++) /*parcours de tabliste*/
        {
            if (tabliste[j].lettre == caract[k]) ///Si on est a la bonne case de tabliste on insere le mot dedans
            {
                Insertfinliste(&tabliste[j].deb, tabmots[i].mot, &tabliste[j].fin);
                break; ///pour s'arreter des qu'on trouve la lettre corresponsante
            }
        }
    }
}

void realloc_chaine(char **cha, char *copy) /**permetla reallocation de l'espace d'une chaine de caractere copy**/
{
    char *char_ptr;
    char_ptr = (char *)malloc(sizeof(char));
    *cha = char_ptr;
    strcpy(*cha, copy);
}
void distribue_2(FILE *fichier, int N, tablist *tabliste, int k) /**distribue les elements du fichier (remplit) dans une liste de caracteres d'alphabet**/
{
    char mot[16] = " ";
    TABMOTS tab[N];
    int i = 0, j;
    char *chaine;
    while (fgets(mot, 16, fichier) != NULL)
    {
        strcpy(tab[i].mot, mot);
        i++;
    }
    char *caract = {0};
    for (i = 0; i < N; i++)
    {
        caract = tab[i].mot;
        for (j = 0; j < 26; j++)
        {
            if (tabliste[j].lettre == caract[k])
            {
                realloc_chaine(&chaine, tab[i].mot); ///Pour ne pas perdre l'adresse du mot en sortant de la procedure on repete l'allocation manuellement dans une copie soit "chaine"
                Insertfinliste(&tabliste[j].deb, chaine, &tabliste[j].fin);
                break; ///pour s'arreter des qu'on trouve la lettre corresponsante
            }
        }
    }
}

/**Procedure principale1:tri des mots se trouvants dans un tableau tabmot **/

void tri_distrib_1(int N, int m, TABMOTS *tabmots, tablist tabliste[]) /**Role:Rend un tableau de mots tri� en ordre alphab�tique "Tri par distribution"**/
{
    int k, i;
    for (k = m; k > 0; k--)
    {
        inittablist(tabliste);                    /*Reinitialisation de tabliste a NIL a chaque iteration*/
        distribue_1(tabmots, N, tabliste, k - 1); ///passage du k par k-1 vu qu'un tableau commence par un 0 en C
        concatlistes_1(tabliste, tabmots, N);     /*Les mots changent d'ordre au fur et a mesure des iteraions dans notre tableau*/
        //l'affichage:
        printf("\nEtape%d ", m - k + 1);
        if (k == m)
        {
            printf("(Derniere lettre):\n");
        }
        else
        {
            if (k != 1)
                printf("(%d-eme lettre):\n", k);
            else
                printf("(premiere lettre):\n", k);
        }
        color(10, 0);
        printf("Sous-classes:");
        int cpt = 0;
        for (i = 0; i < 26; i++)
        {
            pointeur p = tabliste[i].deb;
            if (p != NULL)
            {
                color(10, 15);
                printf("'%c':", tabliste[i].lettre);
                color(0, 15);
            }
            while (p != NULL)
            {
                if (p == tabliste[i].deb)
                {
                    printf("%s", tabmots[cpt].mot);
                    cpt++;
                }
                else
                {
                    printf(",%s", tabmots[cpt].mot);
                    cpt++;
                }
                p = suivant(p);
            }
            if (tabliste[i + 1].deb != NULL)
                printf("   ");
        }
        printf("\nVecteur:{");
        color(0, 15);
        for (i = 0; i < N; i++)
        {
            if (i != 0)
                printf(",%s", tabmots[i].mot);
            else
                printf("%s", tabmots[i].mot);
        }
        printf("}                                                       ");
        color(10, 0);
        if (k != 1)
            printf("\n\n************Etape suivante:\n");
        color(15, 0);
    }
}

/**Procedure principale2:tri des mots se trouvants dans un fichier fichmots **/
void tri_distrib_2(int N, int m, FILE *fichier, tablist tabliste[]) /** tri les elemennts d'un fichier selon la methode de tri par distribution **/
{
    int k, i, cpt = 0;
    for (k = m; k > 0; k--)
    {
        inittablist(tabliste);
        fichier = fopen("fichmots.txt", "r"); ///initialise le tableau de liste
        distribue_2(fichier, N, tabliste, k - 1);
        fclose(fichier); /// distribue les elements de tabliste selon la dernier caractere (k-1)
        fichier = fopen("fichmots.txt", "w+");
        concatlistes_2(tabliste, fichier, N);
        fclose(fichier); ///remplit fichier par les elements de tabliste
        //Affichage:
        char mot[16];
        printf("\nEtape%d ", m - k + 1);
        if (k == m)
        {
            printf("(Derniere lettre):\n");
        }
        else
        {
            if (k != 1)
                printf("(%d-eme lettre):\n", k);
            else
                printf("(premiere lettre):\n", k);
        }
        color(10, 0);
        printf("Sous-classes:\n");
        for (i = 0; i < 26; i++)
        {
            pointeur p = tabliste[i].deb;
            if (p != NULL)
            {
                color(10, 0);
                printf("'%c':\n", tabliste[i].lettre);
                color(15, 0);
            }
            while (p != NULL)
            {
                printf("     %s", valeur(p));
                p = suivant(p);
            }
        }
        fichier = fopen("fichmots.txt", "r");
        cpt = 0;
        printf("\nFichier:\n");
        color(15, 0);
        while (fgets(mot, 16, fichier) != NULL)
        {
            if (cpt != 0)
            {
                printf("%d -%s", cpt + 1, mot);
                cpt++;
            }
            else
            {
                printf("%d -%s", cpt + 1, mot);
                cpt++;
            }
        }
        fclose(fichier);
        color(10, 0);
        if (k != 1)
            printf("\n\n************Etape suivante:\n");
        color(15, 0);
    }
}

/**Programme principal**/

int main()
{

    ///On veut trier des mots alphab�tiquement <en utilisant le tri par distribution> donc on a deux fa�ons d'y proceder:
    /**1-Les mots sont saisis a la main par l'utilisateur**/
    /**2-Les mots sont lus � partir d'un fichier soit fichmots ici**/
    /**Saisie du choix(pour cela on utilise comme outil un menu)**/
    color(3, 15);
    printf(" ECOLE NATIONALE SUPERIEUR D'INFORMATIQUE\n");
    printf("\n");
    printf("\n");
    printf("                           o                                                                                           \n");
    printf("               ___  ____          ___   ___   ___                                                                      \n");
    printf("                |   |__|   |     |_ _| |___| |___|                                                                     \n");
    printf("                |   |  \\   |     |     |   | |   \\                                                                     \n");
    printf("         __     ___ ___  ___  o  ___      ___ O  __                                                                    \n");
    printf("        |  \\ | |___  |  |___| | |___| |  | |  | |  | |\\ |                                                              \n");
    printf("        |__/ | ____| |  |   \\ | |___| |__| |  | |__| | \\| .                                                            \n");
    printf("                                                                                                                       \n");
    printf("                                                                                                                       \n");
    printf("                                                                                                                       \n");
    printf(" ************************************************************************\n");
    printf(" ========================================================================\n");
    printf(" ||                     TP REALISE PAR:                                ||\n");
    printf(" ||          BOUKABOUS RANA   ET   HAFRI SEIFALI                       ||\n");
    printf(" ||                                                                    ||\n");
    printf(" ||                                                                    ||\n");
    printf(" ||                                                                    ||\n");
    printf(" ||                                                                    ||\n");
    printf(" || On veut trier des mots alphabetiquement on utilisant le tri par    ||\n");
    printf(" ||  distribution, donc on a deux facon d'y proceder :                 ||\n");
    printf(" ||  1-\ les mots sont saisis  a la mian par l'utilisateur              ||\n");
    printf(" ||  2-\ les mots sont lus a partir d'un fichier soit fichmots ici      ||\n");
    printf(" ||                                                                    ||\n");
    printf(" ||                                                                    ||\n");
    printf(" ||                                                                    ||\n");
    printf(" ||                                                                    ||\n");
    printf(" ||                                                                    ||\n");
    printf(" ||                                                                    ||\n");
    printf(" ||                                                                    ||\n");
    printf(" ||  Remarque: les mots doivent etre de la meme taille                 ||\n");
    printf(" ||                                                                    ||\n");
    printf(" ||                                                                    ||\n");
    printf(" ||                                                                    ||\n");
    printf(" ||                                                                    ||\n");
    printf(" ************************************************************************\n");
    printf(" ========================================================================");
    int N, m, choix; ///choix:variable du choix;et N et m respectivement le nombre et taille des mots
    color(3, 15);
    printf("\n                     *****Debut du programme*****\n\n");
    color(0, 15);
    printf("\n     S'il vous plait veuillez choisir la facon avec laquelle\n        vous voulez recuperer les mots a trier:\n\n");
    printf("===>'1' pour la saisie au clavier quand leur nombre est inferieur ou egal a 6 \n===>'2' pour la lecture a partir du fichier fichmots sinon\n");
    scanf("%d", &choix);
    if ((choix != 1) || (choix != 2))
    {
        while ((choix != 1) && (choix != 2))
        {
            printf("Veuillez resaisir votre choix SVP\n");
            scanf("%d", &choix);
        }
    }

    printf("\nVeuillez saisir le nombre de vos mots\n");
    scanf("%d", &N);
    printf("\nVeuillez saisir la taille des mots a trier SVP\n");
    scanf("%d", &m);
    TABMOTS tabmots[N];
    /**********************************/ ///Initialsiation des cases de lettres de tabliste
    tablist tabliste[26];
    char *alphabet = {"abcdefghijklmnopqrstuvwxyz"};
    int i;
    for (i = 0; i < 26; i++)
    {
        tabliste[i].lettre = alphabet[i];
    }
    /**********************************/
    FILE *fichier;
    int cpt = 0;
    char mot[16] = " ";
    inittablist(tabliste); //une initialisation pour eviter les erreurs probables
    switch (choix)
    {
    case 1:
        inser_tab_mots(tabmots, N, m);
        printf("Vecteur initial:{");
        for (i = 0; i < N; i++)
        {
            if (i != N - 1)
                printf("%s,", tabmots[i].mot);
            else
                printf("%s", tabmots[i].mot);
        }
        printf("}");
        tri_distrib_1(N, m, tabmots, tabliste);
        break;
    case 2:
        fichier = fopen("fichmots.txt", "w+");
        gener_mot_aleat(N, m, fichier);
        printf("\nFichier initial:\n");
        color(0, 15);
        fichier = fopen("fichmots.txt", "r");
        while (fgets(mot, 16, fichier) != NULL)
        {
            printf("%d -%s", cpt + 1, mot);
            cpt++;
        }
        printf("                                                       ");
        fclose(fichier);
        tri_distrib_2(N, m, fichier, tabliste);
        break;
    }
    color(3, 15);
    printf("\n\n          *****Fin du programme*****     \n");
    system("pause");
    return 0;
}

void color(int textcolor, int backgroundcolor) ///affichage du texte en couleurs
{
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, backgroundcolor * 16 + textcolor);
}

///0:BLACK
///1:BLEU FONCE
///2:VERT FONC�
///3:TURQUOISE
///4:ROUGE FONCE
///5:VIOLET
///6:VERT CACA D'OIE
///7:GRIS CLAIR
///8:GRIS FONCE
///9:BLEU FLUO
///10:VERT FLUO
///11:TURQUOISE
///12:ROUGE FLUO
///13:VIOLET 2
///14:JAUNE
///15:BLANC
