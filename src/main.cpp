#include "app.h"

int main(int argc, char *argv[]){

    ChessApp* app = ChessApp::getInstance();
    app->handleArgs(argc,argv);
    app->init();

    // Event Loop
    app->run();
    return 0;
    
}



