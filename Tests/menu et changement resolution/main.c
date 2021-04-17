#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <stdlib.h>
#include <SDL_image.h>

#define RAPPORT_PARAMETRE_CHOIX 13.5
//PARAMETRE
#define XRAPPORT_GRAPHISMES 2.96
#define XMAXRAPPORT_GRAPHISMES 2.62
#define XRAPPORT_JOUABILITE 2.59
#define XMAXRAPPORT_JOUABILITE 2.33
#define XRAPPORT_INTERFACE 2.30
#define XMAXRAPPORT_INTERFACE 2.09
#define XRAPPORT_SOURISCLAVIER 2.07
#define XMAXRAPPORT_SOURISCLAVIER 1.9
#define XRAPPORT_MANETTE 1.88
#define XMAXRAPPORT_MANETTE 1.74
#define XRAPPORT_AUDIO 1.72
#define XMAXRAPPORT_AUDIO 1.60
#define XRAPPORT_CONTROLES 1.59
#define XMAXRAPPORT_CONTROLES 1.49
#define XRAPPORT_CONTROLESMANETTE 1.47
#define XMAXRAPPORT_CONTROLESMANETTE 1.39
#define XRAPPORT_COMPTE 1.38
#define XMAXRAPPORT_COMPTE 1.30

#define MENU_GRAPHISMES 0
#define MENU_JOUABILITE 1
#define MENU_INTERFACE 2
#define MENU_SOURISCLAVIER 3
#define MENU_MANETTE 4
#define MENU_AUDIO 5
#define MENU_CONTROLES 6
#define MENU_CONTROLESMANETTES 7
#define MENU_COMPTE 8






typedef struct parametres
{
    //GRAPHISMES
    int mode;//0 fenêtré - 1 Plein Ecran - 2 Plein Ecran fenêtré
    int resolution;//variable "compteur" qui détermine la résolution à choisir parmi la liste (voir tableau de résolution)
    int fps;// les fps (30/60/75/144/255/1000
    int affichFPS;//1 afficher les fps - 0 non

    //INTERFACE
    float echelle;//la "taille" de l'interface 0->100%

    //AUDIO
    float musique;//volume musique 0->100%
    float effets;//volume effets sonores 0->100%
    float dialogues;//volume dialogue 0->100%
    float arrierePlan;//volume arrière plan 0->100%

    //CONTROLES

    //JOUEUR 1
    int avancer1;
    int reculer1;
    int sauter1;
    int sneak1;
    int attaquer1;
    int coupspe1;

    //JOUEUR 2
    int avancer2;
    int reculer2;
    int sauter2;
    int sneak2;
    int attaquer2;
    int coupspe2;

    //JOUEUR 3
    int avancer3;
    int reculer3;
    int sauter3;
    int sneak3;
    int attaquer3;
    int coupspe3;

    //JOUEUR 4
    int avancer4;
    int reculer4;
    int sauter4;
    int sneak4;
    int attaquer4;
    int coupspe4;

    //JOYSTICKS/MANETTES
    SDL_Joystick* JOY0;
    SDL_Joystick* JOY1;
    SDL_Joystick* JOY2;
    SDL_Joystick* JOY3;
} parametres;
SDL_Texture *tabMenu[9];
int reso[2][10]= {{1280,1440,1680,1920,1920,768,1280,320,1366,0},
    {800,900,1050,1080,1200,1024,1024,480,768,0}
};
int i;
SDL_Window *fenetre;
SDL_Renderer* rendu;
long int tempsPrecedent, tempsActuel;
float fps;

void chargerTextures()
{
    SDL_Surface *surf;
    char alpha[14]="img/menu/1.png";
    for(int i=0; i<9; i++)
    {
        surf=IMG_Load(alpha);
        SDL_SaveBMP(surf,"test.bmp");

        alpha[9]++;
        tabMenu[i]=SDL_CreateTextureFromSurface(rendu,surf);
        SDL_FreeSurface(surf);
    }
}
void menu_parametres(int page)
{
    SDL_Event event;
    SDL_bool continuer=SDL_TRUE;
    while(continuer)
    {
        while(SDL_PollEvent(&event))
            switch(page)
            {
            case MENU_GRAPHISMES:
                break;
            case MENU_JOUABILITE:
                break;
            case MENU_INTERFACE:
                break;
            case MENU_SOURISCLAVIER:
                break;
            case MENU_MANETTE:
                break;
            case MENU_AUDIO:
                break;
            case MENU_CONTROLES:
                break;
            case MENU_CONTROLESMANETTES:
                break;
            case MENU_COMPTE:
                break;
            }
        tempsActuel = SDL_GetTicks();

        if (tempsActuel - tempsPrecedent  > (1000/fps))
            tempsPrecedent = tempsActuel ;
        else
            SDL_Delay((1000/fps) - (tempsActuel - tempsPrecedent ));
    }
}

void menu()
{
    int a=i;
    if(SDL_GetWindowFlags(fenetre)==5637)a=9;
    SDL_Event event;
    SDL_bool continuer=SDL_TRUE;
    int selecteur_menu=0;
    while(continuer)
    {
        while(SDL_PollEvent(&event))
            switch(event.type)
            {
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    continuer=SDL_FALSE;
                    break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button == SDL_BUTTON_LEFT) //clique gauche
                {
                    printf("clique gauche\n");
                    if(event.button.y<=reso[1][i]/RAPPORT_PARAMETRE_CHOIX) //Selection du menu en question (parametre / audio / . . .
                    {
                        if(event.button.x>=reso[0][a]/XRAPPORT_GRAPHISMES && event.button.x<=reso[0][a]/XMAXRAPPORT_GRAPHISMES)
                            selecteur_menu=0;
                        if(event.button.x>=reso[0][a]/XRAPPORT_JOUABILITE && event.button.x<=reso[0][a]/XMAXRAPPORT_JOUABILITE)
                            selecteur_menu=1;
                        if(event.button.x>=reso[0][a]/XRAPPORT_INTERFACE && event.button.x<=reso[0][a]/XMAXRAPPORT_INTERFACE)
                            selecteur_menu=2;
                        if(event.button.x>=reso[0][a]/XRAPPORT_SOURISCLAVIER && event.button.x<=reso[0][a]/XMAXRAPPORT_SOURISCLAVIER)
                            selecteur_menu=3;
                        if(event.button.x>=reso[0][a]/XRAPPORT_MANETTE && event.button.x<=reso[0][a]/XMAXRAPPORT_MANETTE)
                            selecteur_menu=4;
                        if(event.button.x>=reso[0][a]/XRAPPORT_AUDIO && event.button.x<=reso[0][a]/XMAXRAPPORT_AUDIO)
                            selecteur_menu=5;
                        if(event.button.x>=reso[0][a]/XRAPPORT_CONTROLES && event.button.x<=reso[0][a]/XMAXRAPPORT_CONTROLES)
                            selecteur_menu=6;
                        if(event.button.x>=reso[0][a]/XRAPPORT_CONTROLESMANETTE && event.button.x<=reso[0][a]/XMAXRAPPORT_CONTROLESMANETTE)
                            selecteur_menu=7;
                        if(event.button.x>=reso[0][a]/XRAPPORT_COMPTE && event.button.x<=reso[0][a]/XMAXRAPPORT_COMPTE)
                            selecteur_menu=8;
                    }
                }
                break;
            case SDL_QUIT:
                continuer=SDL_FALSE;
                break;

            }
        SDL_RenderCopy(rendu, tabMenu[selecteur_menu], NULL, NULL);
        SDL_RenderPresent(rendu);
        tempsActuel = SDL_GetTicks();

        if (tempsActuel - tempsPrecedent  > (1000/fps))
            tempsPrecedent = tempsActuel ;
        else
            SDL_Delay((1000/fps) - (tempsActuel - tempsPrecedent ));
    }

}

int main(int argc, char * argv[])
{
    int db=1;
    i=0;
    fps=500;
    float total;
    tempsPrecedent = 0;
    tempsActuel = 0;
    char *chaine;
    SDL_Color blanc = {0,0,0};
    SDL_Rect positionTitre= {0,0,100,35};
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    fenetre=SDL_CreateWindow("TEST RESIZE TEXTURE",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,reso[0][0],reso[1][0],SDL_WINDOW_SHOWN);
    rendu=SDL_CreateRenderer(fenetre,-1,SDL_RENDERER_ACCELERATED);
    TTF_Init();
    TTF_Font *police = TTF_OpenFont("police.ttf",50);
    SDL_Surface *surf1=IMG_Load("img/test1.jpg"),*text=NULL;
    SDL_Texture* image=SDL_CreateTextureFromSurface(rendu,surf1),*textfps;
    int fenetreW,fenetreH;
    SDL_Event event;

    //charger textures
    chargerTextures();

    //JOYSTICKS
    SDL_Joystick* JOY1=SDL_JoystickOpen(0);
    SDL_JoystickEventState(SDL_ENABLE);
    /*
    printf("Informations du joystick\n");

    printf("Nombre d'axes : %d\n",SDL_JoystickNumAxes(JOY1));
    printf("Nombre de chapeaux : %d\n",SDL_JoystickNumHats(JOY1));
    printf("Nombre de trackballs : %d\n",SDL_JoystickNumBalls(JOY1));
    printf("Nombre de boutons : %d\n",SDL_JoystickNumButtons(JOY1));
    */
    printf("Nom : %s\n",SDL_JoystickName(0));
    printf("Nom : %s\n",JOY1);

    while(db)
    {
        while(SDL_PollEvent(&event))
            switch(event.type)
            {
            case SDL_KEYDOWN :
                switch(event.key.keysym.sym)
                {
                case SDLK_UP:
                    if(i<=7 && SDL_GetWindowFlags(fenetre)!=5637)++i;
                    SDL_SetWindowSize(fenetre,reso[0][i],reso[1][i]);
                    printf("%d %d\n", reso[0][i],reso[1][i]);
                    SDL_SetWindowPosition(fenetre,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED);

                    break;
                case SDLK_DOWN:
                    if(i>=1 && SDL_GetWindowFlags(fenetre)!=5637)--i;
                    SDL_SetWindowSize(fenetre,reso[0][i],reso[1][i]);
                    printf("%d %d\n", reso[0][i],reso[1][i]);
                    SDL_SetWindowPosition(fenetre,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED);

                    break;
                case SDLK_RIGHT:
                    SDL_SetWindowFullscreen(fenetre,SDL_WINDOW_FULLSCREEN_DESKTOP);
                    SDL_GetWindowSize(fenetre,&fenetreW,&fenetreH);
                    printf("PLEIN ECRAN \n");
                    reso[0][9]=fenetreW;
                    reso[1][9]=fenetreH;
                    break;
                case SDLK_LEFT:
                    if(reso[0][9]==fenetreW && reso[1][9]==fenetreH)
                    {
                        SDL_SetWindowFullscreen(fenetre,SDL_WINDOW_SHOWN);
                        //SDL_RestoreWindow(fenetre);
                        //SDL_MaximizeWindow(fenetre);
                        SDL_SetWindowSize(fenetre,reso[0][i],reso[1][i]);
                        SDL_SetWindowPosition(fenetre,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED);
                    }
                    break;
                case SDLK_i:
                    menu();
                    break;
                case SDLK_e:
                    SDL_DestroyRenderer(rendu);
                    rendu=SDL_CreateRenderer(fenetre,-1,SDL_RENDERER_ACCELERATED);
                    break;
                case SDLK_r:
                    SDL_DestroyRenderer(rendu);
                    rendu=SDL_CreateRenderer(fenetre,-1,SDL_RENDERER_SOFTWARE);
                    break;
                }
                break;

            case SDL_JOYBUTTONDOWN:
                printf("Boutton:%d\n",event.jbutton.button);
                break;
            case SDL_JOYAXISMOTION:
                printf("axe:%d avec valeur:%d\n",event.jaxis.axis,event.jaxis.value);
                break;

            case SDL_WINDOWEVENT:
                //mode fenetr�
                break;
            case SDL_QUIT :
                db=0;
                break;
            }
        SDL_RenderCopy(rendu, image, NULL, NULL);
        //delay
        tempsActuel = SDL_GetTicks();

        if ((tempsActuel - tempsPrecedent)  > (1000/fps)) tempsPrecedent = tempsActuel ;
        else                                            SDL_Delay((1000/fps) - (tempsActuel - tempsPrecedent ));

        total=1000/(!(tempsActuel - tempsPrecedent)?1:(tempsActuel - tempsPrecedent));

        if(total>fps)   sprintf(chaine,"FPS : %g",fps);
        else            sprintf(chaine,"FPS : %g",total);

        text = TTF_RenderText_Solid(police,chaine,blanc);
        if(text!=NULL)
        {
            if(SDL_GetWindowFlags(fenetre)!=5637)
            {
                positionTitre.x = (reso[0][i]*0.9);
                positionTitre.y = (reso[1][i]*0.95);
            }
            else
            {
                positionTitre.x = (reso[0][9]*0.9);
                positionTitre.y = (reso[1][9]*0.95);
            }
            textfps=SDL_CreateTextureFromSurface(rendu,text);

            SDL_RenderCopy(rendu, textfps, NULL, &positionTitre);

            SDL_FreeSurface(text);
            SDL_DestroyTexture(textfps);
        }
        SDL_RenderPresent(rendu);
    }

    //On fait le m�nage et on remet les pointeurs � NULL
    SDL_DestroyRenderer(rendu);
    rendu = NULL;
    SDL_DestroyWindow(fenetre);
    fenetre = NULL;

    //On quitte SDL_TTF 2
    IMG_Quit();

    //On quitte la SDL
    SDL_Quit();
    return 0;
}
