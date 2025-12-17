/**
 * @file GraphFileIO.h
 * @brief ͼ�ļ�������������ࣨ��STL�汾��
 * @class GraphFileIO
 * @brief ʹ��ԭ������ʵ�֣������ȡ�ڵ������ļ�������ͼ�ṹ
 */

#pragma once
#ifndef GRAPH_FILE_IO_H
#define GRAPH_FILE_IO_H

#include "Graph.h"
#include <cstdio>
#include <cmath>

class GraphFileIO {
private:
    static const int MAX_NODES = 1000;  // ���ڵ���
    static const int MAX_LINE_LENGTH = 256;  // ����г���

public:
    /**
     * @brief ���ļ���ȡ�ڵ����겢��䵽ͼ����
     * @param graph Ҫ����ͼ��������
     * @param filename �����ڵ�������ļ�·��
     * @return bool �ɹ�����true��ʧ�ܷ���false
     */
    static bool readNodesAndBuildGraph(Graph& graph, const char* filename);

    /**
     * @brief ��֤�ļ���ʽ�Ƿ���Ч
     * @param filename Ҫ��֤���ļ�·��
     * @return bool �ļ���ʽ��Ч����true�����򷵻�false
     */
    static bool validateFile(const char* filename);
    
    /**
     * @brief ���ļ��ȡ��������
     * @param filename Ҫ��ȡ���ļ�·��
     * @return int �ļ��в���������-1��ʾ���ɹ�
     */
    static int readVertexCountOnly(const char* filename);

private:
    /**
     * @brief ����������ŷ����þ���
     */
    static double calculateDistance(double x1, double y1, double x2, double y2);

    /**
     * @brief ���ļ���ȡ��������
     */
    static int readVertexCount(FILE* file, const char* filename);

    /**
     * @brief ��ȡ���ж������굽����
     */
    static int readCoordinates(FILE* file, int vertexCount, double* xCoords, double* yCoords, const char* filename);

    /**
     * @brief �ַ���ת��Ϊ����
     */
    static int stringToInt(const char* str);

    /**
     * @brief �ַ���ת��Ϊ������
     */
    static double stringToDouble(const char* str);

    /**
     * @brief ȥ���ַ������˿հ��ַ�
     */
    static void trimString(char* str);

    /**
     * @brief ��ȫ���ַ�������
     */
    static void stringCopy(char* dest, const char* src, int maxLen);

    /**
     * @brief �����ַ�������
     */
    static int stringLength(const char* str);
};

#endif // GRAPH_FILE_IO_H