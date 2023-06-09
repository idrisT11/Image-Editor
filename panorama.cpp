#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/stitching.hpp"
#include <iostream>
#include <filesystem>
#include <string>


using namespace std;
using namespace cv;

vector<String> imagesNames;     // Vector containing imagefiles names

vector<Mat> imgs = {};          // Vector containing Mat
bool isImage(String);           // Function returning whether the file is a readable file
String folderSelection();       // Function that retrieves the path to the folder where the images are stored
String convertToPath(String);   // Function processing a character string to change it into a path




int main(){

    String namePath = folderSelection();      // Path leading to the folder
    filesystem::path path = filesystem::path(namePath);     // Conversion String to filesystem::path
    vector<String> namesImagesFiles;            // Vector containing the names of each image file


    // Accesses every file in the folder
    for (const auto & entry : filesystem::directory_iterator(path)){
        const String fileName = entry.path().string();   // We collect all paths and we convert them to Strings (originally : filesystem::path)
        if (isImage(fileName)){                 // If the file is an image
            imagesNames.push_back(fileName);   // Insert the path (String) in imagesNames
        }
    }


    // Store images in a vector<Mat>
    for (int i = 0; i < imagesNames.size(); i++){
        Mat img = imread(imagesNames[i]);
        if (img.empty()){
            cout<<imagesNames[i]<<" - Cannot read image"<<endl;
            return -1;
        }
        imgs.push_back(img);
    }


    // Build a panorama
    Mat panorama;       // Matrix that will contain the final image
    Stitcher::Mode mode = Stitcher::PANORAMA;       // Mode panorama
    Ptr<Stitcher> stitcher = Stitcher::create(mode);
    Stitcher::Status status = stitcher->stitch(imgs, panorama);     // Build panorama
    cout<<"Status : "<<status<<endl;
    if (status != Stitcher::OK) {                   // If not success
        cout << "Cannot stitch images" << endl;
        return -1;
    }
    std::filesystem::create_directory(namePath+"\\\\PANORAMA");         // Create a directory where store the result image
    imwrite(namePath+"\\\\PANORAMA\\\\panorama.jpg", panorama); // Save image in this directory
    imshow("Result", panorama);         // Plot image
    waitKey(0);
    return 0;
}





String folderSelection(){
    do {
        String folderName;
        std::cout<<"Please, enter the path of the folder containing the images"<<std::endl;
        std::cin >> folderName;
        std::cout << "\nDo you confirm ? \n(Yes : Press 1) \n(No : Press 0)"<<std::endl;
        char answer;
        do{
            std::cin >> answer;
        }while(answer!=char(48) && answer != char(49));
        if (answer == char(49)){
            folderName = convertToPath(folderName);
            return folderName;
        }
    } while(1);
}





bool isImage(const String fileName){

    // Source : imread() documentation
    const vector<String> authorizedExtensions = {".bmp", ".dib", ".jpeg", ".jpg", ".jpe", ".jp2",
                                                 ".png", ".webp", ".pbm", ".pgm", ".ppm", ".pxm",
                                                 ".pnm", ".sr", ".ras", ".tiff", ".tif", ".exr",
                                                 ".hdr", ".pic"};   // List of all extensions accepted by imread
    for (int i=0; i<authorizedExtensions.size(); i++){
        String extension = authorizedExtensions[i];
        if(extension.size() < fileName.size()){     // Check that extension is longer than filename in order to avoid errors
            if (std::equal(begin(extension), end(extension), end(fileName)-extension.size())){  // If fileName ends by extension
                return true;        //  Then, this file is an image
            }
        }
    }
    return false;       // This file isn't an image
}





String convertToPath(String filename){
    // Delete " if necessary
    while (filename.find('"') != 18446744073709551615) {    // find return 18446744073709551615 if the character is not found
        int pos = filename.find('"');
        filename.erase(pos, 1);
    }

    // Converts all "/" to "//" if necessary
    int i = 1;
    while (i!= filename.size()-1){
        if (filename[i] == '\\' && filename[i-1] != '\\' && filename[i+1] != '\\'){
            filename.insert(i,"\\");
        }
        i++;
    }
    return filename;
}