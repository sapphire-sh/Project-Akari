// Ŭnicode please
#include "stdafx.h"

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

//임시 테스트용
void DrawAxis() {
    glPushMatrix();
    glLineWidth(2.0f);

    glBegin(GL_LINES);
    //x
    glColor4f(1, 0, 0, 1);
    glVertex3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(-1, 0, 0);
    glVertex3f(0, 0, 0);

    //y
    glColor4f(0, 1, 0, 1);
    glVertex3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, -1, 0);
    glVertex3f(0, 0, 0);

    //z
    glColor4f(0, 0, 1, 1);
    glVertex3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, -1);
    glVertex3f(0, 0, 0);
    
    glEnd();

    glPopMatrix();
}

int main(void) {

    const int w = 1024, h = 768;

    int running = GL_TRUE;
    // Initialize GLFW
    if( !glfwInit() ) {
        exit( EXIT_FAILURE ); 
    }

    // Open an OpenGL window 
    if( !glfwOpenWindow( w, h, 0, 0, 0, 0, 0, 0, GLFW_WINDOW ) ) {
        glfwTerminate(); 
        exit( EXIT_FAILURE ); 
    }
    glfwSetWindowTitle("Project Akari");

    //Init setting
    glEnable (GL_DEPTH_TEST);
    glClearColor(1, 1, 1, 1);
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //직교 투영
    glOrtho(-1, 1, -1, 1, 1, 1000);
    //원근 투영
    //glFrustum(-1, 1, -1, 1, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
    
    // Main loop 
    while( running ) {
        // OpenGL rendering goes here... 
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        glLoadIdentity();
        gluLookAt(1, 1, 1, 0, 0, 0, 0, 1, 0);

        DrawAxis();
        // Swap front and back rendering buffers 
        glfwSwapBuffers();
        // Check if ESC key was pressed or window was closed 
        running = !glfwGetKey( GLFW_KEY_ESC ) && glfwGetWindowParam( GLFW_OPENED );
    }
    // Close window and terminate GLFW 
    glfwTerminate();
    // Exit program 
    exit( EXIT_SUCCESS );

    return 0;
}