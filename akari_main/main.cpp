// Ŭnicode please
#include "stdafx.h"
#include "terrain.h"
#include "camera.h"

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

#define WINDOW_WIDTH (1024)
#define WINDOW_HEIGHT (768)

//임시 테스트용
void DrawAxis() {

    const static float length = 1000;

    glPushMatrix();
    glPushAttrib(GL_CURRENT_BIT);

    glLineWidth(2.0f);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_LINES);
    //x
    glColor4f(1, 0, 0, 1);
    glVertex3f(-length/2, 0, 0);
    glVertex3f(length/2, 0, 0);
    
    //y
    glColor4f(0, 1, 0, 1);
    glVertex3f(0, -length/2, 0);
    glVertex3f(0, length/2, 0);
    
    //z
    glColor4f(0, 0, 1, 1);
    glVertex3f(0, 0, -length/2);
    glVertex3f(0, 0, length/2);

    glEnd();

    glPopAttrib();
    glPopMatrix();
}

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

    akari::Terrain terr(512, 512);
    akari::Camera camera;

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

        terr.Draw(0);
        DrawAxis();

        glFlush();

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