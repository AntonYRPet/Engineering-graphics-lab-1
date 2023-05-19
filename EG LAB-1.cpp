#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "math_3d.h"

GLuint VBO; //глобальна€ переменна€ дл€ хранени€ указател€ на буфер вершин

void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT); //ќчистка буфера кадра

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO); 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawArrays(GL_TRIANGLES, 0, 3); //основна€ функци€ дл€ рисовани€

    glDisableVertexAttribArray(0);

    glutSwapBuffers(); //помен€ть фоновый буфер и буфер кадра местами
}

void CreateVertexBuffer()
{
    Vector3f Vertices[3]; //создаем массив из одного экземпл€ра структуры Vector3f (этот тип объ€влен в math_3d.h) и задаЄм XYZ по нул€м
    Vertices[0] = Vector3f(-1.0f, -1.0f, 0.0f);
    Vertices[1] = Vector3f(1.0f, -1.0f, 0.0f);
    Vertices[2] = Vector3f(0.0f, 1.0f, 0.0f);
 	glGenBuffers(5, &VBO); //1 - количество создаваемых объектов 2 - ссылка на массив GLuint
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //GL_ARRAY_BUFFER означает, что буфер будет хранить массив вершин
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW); // цели(такое же как и при прив€зывании), размер данных в байтах, адрес массива вершин, и флаг, который обозначает использование паттернов дл€ этих данных
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv); //инициализаци€ glut
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA); //GLUT_DOUBLE включает двойную буферизацию
    //задаЄм параметры окна, даЄм заголовок
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("LAB-1");
    

    glutDisplayFunc(RenderSceneCB); 

    GLenum res = glewInit(); //инициализируем GLEW и провер€ем на ошибки
    if (res != GLEW_OK) {
      fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
      return 1;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); 
    glColor3f(0.5f, 0.0f, 0.0f);        
    CreateVertexBuffer();

    glutMainLoop(); //передать контроль GLUT'y который начинает собственный цикл

    return 0;
}


