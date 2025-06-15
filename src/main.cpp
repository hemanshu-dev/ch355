#include "app.h"

int main(int argc, char *argv[]){

    ChessApp* app = ChessApp::getInstance();
    app->handleArgs(argc,argv);
    app->init();
    // eventLoop
    app->run();
    return 0;
    
}



