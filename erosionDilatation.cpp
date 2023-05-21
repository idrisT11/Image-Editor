
#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/highgui.hpp"


using namespace cv;

Mat im_src, im_dst;            // im_src = image source ; im_dst = image destination

bool makeErosion = true;                 // Booléen indiquant si on effectue une erosion (true/1) ou une dilatation (false/0)

int kernel_type = 0;       // Définition par défaut du type d'érosion (0 : Carré, 1: Croix, 2: Ellipse)
int kernel_size = 0;       // Définition par défaut de la taille de l'érosion

int const max_kernel_type = 2;          // Constante ; Valeur du nombre de types disponibles (2+1) types
int const max_kernel_size = 15;         // Constante ; Valeur taille maximale du noyau (2*15 + 1)

void Erosion(int, void*);
void Dilatation(int, void*);
void changeButton(int, void*);


int main(int argc, char** argv) {

    String source = "C:\\Users\\Benjamin\\Downloads\\tennis.jpg";       // A SUPPRIMER, lien vers image pour tests
    im_src = imread(source, IMREAD_COLOR);      // Lecture d'image

    if (im_src.empty()){            // Si vide
        std::cout << "Opening failed" << std::endl;     // Indiquer une erreur
        return -1;                  // Renvoyer une erreur et stopper la lecture
    }

    //namedWindow("Image originale", WINDOW_AUTOSIZE);        // Créer fenêtre pour l'image originale
    namedWindow("Image obtenue", WINDOW_AUTOSIZE);          // Créer fenêtre pour l'image résultat

    moveWindow("Image obtenue", im_src.cols, 0);     // Déplace la fenêtre au point désigné par x et y
    // im_src.cols : renvoie le nombre de colonnes dans l'image => Les deux fenêtres sont côte-à-côte

    // Voir createButton


    if (makeErosion){
        setWindowTitle("Image obtenue", "Erosion");
        createTrackbar("Kernel type", "Image obtenue", &kernel_type, max_kernel_type, Erosion);
        createTrackbar("Kernel size", "Image obtenue", &kernel_size, max_kernel_size, Erosion);
    } else {
        setWindowTitle("Image obtenue", "Dilatation");
        createTrackbar("Kernel type", "Image obtenue", &kernel_type, max_kernel_type, Dilatation);
        createTrackbar("Kernel size", "Image obtenue", &kernel_size, max_kernel_size, Dilatation);
    }

    Erosion(0, 0);
    Dilatation(0, 0);
    //imshow("Image originale", im_src);
    imshow("Image obtenue", im_dst);
    waitKey(0);
    return 0;
}





void Erosion( int, void* )
{
    int erosion_type = 0;           // Type d'érosion (Rectangle, Croix, Ellipse) stocke le MorphShape correspondant à erosion_elem

    switch(kernel_type){
        case 0:                     // Noyau rectangulaire
            erosion_type = MORPH_RECT;
            break;
        case 1:                     // Noyau en croix
            erosion_type = MORPH_CROSS;
            break;
        case 2:                     // Noyau en ellipse
            erosion_type = MORPH_ELLIPSE;
            break;
        default:                    // Sinon : erreur
            std::cout<<"kernel_type ne correspond pas à une valeur autorisée. Remise à la valeur par défaut : ellipse"<<std::endl;
            erosion_type = MORPH_ELLIPSE;

    }

    // Create kernel
    Mat kernel = getStructuringElement( erosion_type,
                                        Size(2*kernel_size + 1, 2*kernel_size+1),
                                        Point(kernel_size, kernel_size) );
    erode( im_src, im_dst, kernel);
    imshow( "Image obtenue", im_dst);
}





void Dilatation(int, void*)
{
    int dilatation_type = 0;           // Type de dilatation (Rectangle, Croix, Ellipse) stocke le MorphShape correspondant à erosion_elem

    switch(kernel_type){
        case 0:                     // Noyau rectangulaire
            dilatation_type = MORPH_RECT;
            break;
        case 1:                     // Noyau en croix
            dilatation_type = MORPH_CROSS;
            break;
        case 2:                     // Noyau en ellipse
            dilatation_type = MORPH_ELLIPSE;
            break;
        default:                    // Sinon : erreur
            std::cout<<"kernel_type ne correspond pas à une valeur autorisée. Remise à la valeur par défaut : ellipse"<<std::endl;
            dilatation_type = MORPH_ELLIPSE;

    }

    // Create kernel
    Mat kernel = getStructuringElement( dilatation_type,
                                        Size(2*kernel_size + 1, 2*kernel_size+1),
                                        Point(kernel_size, kernel_size) );
    dilate( im_src, im_dst, kernel);
    imshow( "Image obtenue", im_dst);
}




void changeButton(int, void*){

}