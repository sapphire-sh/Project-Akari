// Ŭnicode please
#include "stdafx.h"
#include "terrain.h"
#include "camera.h"
#include "bitmap.h"
#include "info_ui.h"

/*
　　　　　　　　　　　　　　　　　　　　　　 - - ､　　　　　　　　　　- -
　　　 ‐ - 、　　　_人_　　‥ _ _ - ¨　‐ '　　 ￤　　　　 　 　, ′　　 l
　　 ￤　　 丶　　｀Y´　 ￤　　　　　　　　　　` ､　　　　　　'　　　 　 l
　　 ⅰ　　　 丶　　　　　冫　　　　　　　　　 　 '′　　　　｣　　　 　〃
　 　 丶　　　　!､　　　　' 、　　　　　　　　　　｢　　　 　 イ　{｀ - ‐ ′
　　　　 ヽ _ ,, '　 ＼　　　 ⅰ　　　　　　　 　 ⅰ　 　 　 /　　r┘　|
　　　　　　|,、＼_ _｢　　　 ￤　　　　　　　 ､, ヽ!　　　　勹　_,.ｨ_j＾'′_人_
　　　　　　　ﾚﾍ.,_ ヽ　　　　l ,' v 'v i　　；｀ -　､　　　　 /,ノ　‥､ 　 ｀Y´
　　　　　　　　　　ヽﾍ　　　　　　‥'　 　 ´　　　ヽ 　　〃 　,' 　 l
_人_　　　　　　　‥ ＼丶　 　,' 　　　　　　　　　　` ､/_ 　´　,　'
｀Y´　　　　　　 ￤　；　＼）　 '　　　　　　　　 ｢ ､　　　　　 '　
　　　　￣￣/　 丶 　` ､ _ _ '　　'　　　　　　　l 　` ､_,.　´
　　　　 　 |　　　　 ` ､　　　　 , '￤　　　　　　 l 　　　　　　　　　｀¨　／
　　　　 　 | 　　l l　 　 ` ･ ､ , '|　　　　　　|　|　 !_,,..-――--　　　／
　　　　　　　　　／　　　　　￣冂 l　　　　　/　　l
　　　　　　　　　　　　　　　　　　 ￤　　 　 ′ 　 l
*/

void Init() {
    glfwSetWindowTitle("Project Akari");

    //Init setting
    glEnable (GL_DEPTH_TEST);
    glClearColor(1, 1, 1, 1);
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //원근 투영
    glm::mat4 per_mat = glm::perspective(45.0f, (float)(WINDOW_WIDTH)/(WINDOW_HEIGHT), 0.1f, 100.0f);
    glLoadMatrixf((GLfloat*)&per_mat);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(void) {

    akari::Terrain terr(10, 10, 0);
    akari::Camera camera;
    akari::InfoUI info_ui;
    akari::Bitmap bitmap_mgr;

    //file open/save dialog
    OPENFILENAME ofn ;

    wchar_t szFile[260];
    
    ZeroMemory(&ofn , sizeof(ofn));
    ofn.lStructSize = sizeof (ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = L"Bitmap File\0*.bmp\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir= NULL;
    ofn.Flags = OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST;



    //temp input managing
    bool is_rotating_ = false;
    bool is_rotating_pressing_ = false;


    int running = GL_TRUE;
    // Initialize GLFW
    if( !glfwInit() ) {
        exit( EXIT_FAILURE ); 
    }

    // Open an OpenGL window 
    if( !glfwOpenWindow( WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, 0, 0, 0, 0, GLFW_WINDOW ) ) {
        glfwTerminate(); 
        exit( EXIT_FAILURE ); 
    }

    Init();    
    
    // Main loop 
    while( running ) {
        // OpenGL rendering goes here... 
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        glLoadIdentity();

        camera.Update();

        if(is_rotating_) {
            glRotatef(glfwGetTime() * 75, 0, 1, 0);
        }

		terr.Update(camera.GetEye(),camera.GetLookAt());
        terr.Draw(0, is_rotating_);
        
        info_ui.DrawHelp();
        info_ui.DrawTerrainInfo(terr);
        info_ui.DrawAxis();
        info_ui.DrawCameraInfo(camera);
        info_ui.DrawIsRotating(is_rotating_);

        glFlush();

        // Swap front and back rendering buffers 
        glfwSwapBuffers();

        // Check if ESC key was pressed or window was closed 
        running = !glfwGetKey( GLFW_KEY_ESC ) && glfwGetWindowParam( GLFW_OPENED );

		if(glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT)) {
			terr.Click();
        }
        if(!is_rotating_pressing_ && glfwGetKey('M') == GLFW_PRESS) {
            is_rotating_ = !is_rotating_;
            is_rotating_pressing_ = true;
        }
        if(glfwGetKey('M') == GLFW_RELEASE) {
            is_rotating_pressing_ = false;
        }
        //File Open
        if(glfwGetKey('O') == GLFW_PRESS) {
            if(GetOpenFileName(&ofn)) {
                bitmap_mgr.ImportBMP(terr, ofn.lpstrFile);
                MessageBox ( NULL , ofn.lpstrFile , L"Open File" , MB_OK);
            }
        }

        if(glfwGetKey('P') == GLFW_PRESS) {
            if(GetSaveFileName(&ofn)) {
                bitmap_mgr.ExportBMP(terr, ofn.lpstrFile);
                MessageBox ( NULL , ofn.lpstrFile , L"Saved." , MB_OK);
            }
        }
    }
    // Close window and terminate GLFW 
    glfwTerminate();
    // Exit program 
    exit( EXIT_SUCCESS );

    return 0;
}