cmake_minimum_required(VERSION 3.27)
project(projeto00 C)

set(CMAKE_C_STANDARD 11)

add_executable(projeto00 main.c
        aluno.c
        aluno.h
        professor.c
        professor.h
        disciplina.c
        disciplina.h
        relatorios.c
        relatorios.h)
