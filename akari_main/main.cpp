// Ŭnicode please
#include <GL/glfw.h>
#include <cstdlib>

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

int main(void) {

    int running = GL_TRUE;
    // Initialize GLFW
    if( !glfwInit() ) {
        exit( EXIT_FAILURE ); 
    }

    // Open an OpenGL window 
    if( !glfwOpenWindow( 300,300, 0,0,0,0,0,0, GLFW_WINDOW ) ) {
        glfwTerminate(); exit( EXIT_FAILURE ); 
    }

    // Main loop 
    while( running ) {
        // OpenGL rendering goes here... 
        glClear( GL_COLOR_BUFFER_BIT );
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