/**
 * @file GraphFileIO.cpp
 * @brief ͼ�ļ��������������ʵ�֣���STL�汾��
 */

#include "GraphFileIO.h"
#include <cctype>
#include <cstdlib>
#include <cerrno>
#include <stdexcept>

 // �����ַ�������
int GraphFileIO::stringLength(const char* str) {
    int len = 0;
    while (str[len] != '\0') len++;
    return len;
}

// ��ȫ�ַ�������
void GraphFileIO::stringCopy(char* dest, const char* src, int maxLen) {
    int i = 0;
    while (i < maxLen - 1 && src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

// ȥ���ַ������˿հ�
void GraphFileIO::trimString(char* str) {
    if (str == nullptr) return;

    int len = stringLength(str);
    int start = 0, end = len - 1;

    // �ҵ���һ���ǿհ��ַ�
    while (start <= end && (str[start] == ' ' || str[start] == '\t' || str[start] == '\n' || str[start] == '\r')) {
        start++;
    }

    // �ҵ����һ���ǿհ��ַ�
    while (end >= start && (str[end] == ' ' || str[end] == '\t' || str[end] == '\n' || str[end] == '\r')) {
        end--;
    }

    // �ƶ��ַ�������
    if (start > 0) {
        int i = 0;
        for (int j = start; j <= end; j++, i++) {
            str[i] = str[j];
        }
        str[i] = '\0';
    }
    else if (end < len - 1) {
        str[end + 1] = '\0';
    }
}

// �ַ���ת����
int GraphFileIO::stringToInt(const char* str) {
    if (str == nullptr) return 0;

    int result = 0;
    int sign = 1;
    int i = 0;

    // ��������
    if (str[0] == '-') {
        sign = -1;
        i++;
    }
    else if (str[0] == '+') {
        i++;
    }

    // ת������
    while (str[i] != '\0') {
        if (str[i] >= '0' && str[i] <= '9') {
            // ������
            if (result > INT_MAX / 10 || (result == INT_MAX / 10 && (str[i] - '0') > INT_MAX % 10)) {
                return sign == 1 ? INT_MAX : INT_MIN;
            }
            result = result * 10 + (str[i] - '0');
            i++;
        }
        else {
            break;  // �����������ַ�ֹͣ
        }
    }

    return sign * result;
}

// �ַ���ת������
double GraphFileIO::stringToDouble(const char* str) {
    if (str == nullptr) return 0.0;

    double result = 0.0;
    double fraction = 1.0;
    int sign = 1;
    int i = 0;
    bool hasDecimal = false;

    // ��������
    if (str[0] == '-') {
        sign = -1;
        i++;
    }
    else if (str[0] == '+') {
        i++;
    }

    // ת���������ֺ�С������
    while (str[i] != '\0') {
        if (str[i] == '.') {
            hasDecimal = true;
            i++;
            continue;
        }

        if (str[i] >= '0' && str[i] <= '9') {
            if (!hasDecimal) {
                result = result * 10.0 + (str[i] - '0');
            }
            else {
                fraction *= 0.1;
                result += (str[i] - '0') * fraction;
            }
            i++;
        }
        else {
            break;  // �����������ַ�ֹͣ
        }
    }

    return sign * result;
}

// ����ŷ����þ���
double GraphFileIO::calculateDistance(double x1, double y1, double x2, double y2) {
    // ������֤
    if (std::isnan(x1) || std::isnan(y1) || std::isnan(x2) || std::isnan(y2)) {
        return -1.0;  // �����ʶ
    }

    double deltaX = x2 - x1;
    double deltaY = y2 - y1;

    return std::sqrt(deltaX * deltaX + deltaY * deltaY);
}

// ��ȡ��������
int GraphFileIO::readVertexCount(FILE* file, const char* filename) {
    char line[MAX_LINE_LENGTH];

    // ��ȡ��һ��
    if (std::fgets(line, MAX_LINE_LENGTH, file) == nullptr) {
        std::fprintf(stderr, "�����޷���ȡ�ļ���һ�� %s\n", filename);
        return -1;
    }

    trimString(line);
    if (stringLength(line) == 0) {
        std::fprintf(stderr, "�����ļ���һ��Ϊ�� %s\n", filename);
        return -1;
    }

    int vertexCount = stringToInt(line);

    // ��֤��������
    if (vertexCount <= 0) {
        std::fprintf(stderr, "���󣺶���������Ϊ���������õ� %d\n", vertexCount);
        return -1;
    }

    if (vertexCount > MAX_NODES) {
        std::fprintf(stderr, "���󣺶���������������� %d > %d\n", vertexCount, MAX_NODES);
        return -1;
    }

    return vertexCount;
}

// ��ȡ��������
int GraphFileIO::readCoordinates(FILE* file, int vertexCount, double* xCoords, double* yCoords, const char* filename) {
    char line[MAX_LINE_LENGTH];
    int coordinatesRead = 0;

    for (int i = 0; i < vertexCount; i++) {
        if (std::fgets(line, MAX_LINE_LENGTH, file) == nullptr) {
            std::fprintf(stderr, "�����ļ�������������� %d �����꣬��ֻ������ %d ��\n", vertexCount, i);
            return -1;
        }

        trimString(line);
        if (stringLength(line) == 0) {
            continue;  // ��������
        }

        // ��������������
        char* token = line;
        int coordIndex = 0;
        bool success = true;

        while (*token != '\0' && coordIndex < 2) {
            // �����հ�
            while (*token == ' ' || *token == '\t') token++;

            if (*token == '\0') break;

            // ��ȡ����
            char number[32];
            int numIndex = 0;

            while ((*token >= '0' && *token <= '9') || *token == '.' || *token == '-' || *token == '+') {
                if (numIndex < 31) {
                    number[numIndex++] = *token;
                }
                token++;
            }
            number[numIndex] = '\0';

            if (numIndex > 0) {
                double value = stringToDouble(number);

                if (coordIndex == 0) {
                    xCoords[coordinatesRead] = value;
                }
                else {
                    yCoords[coordinatesRead] = value;
                }
                coordIndex++;
            }

            // �����ָ���
            while (*token == ' ' || *token == '\t') token++;
        }

        if (coordIndex == 2) {
            coordinatesRead++;
        }
        else {
            std::fprintf(stderr, "���棺�� %d �������ʽ��Ч: %s\n", i + 2, line);
        }
    }

    return coordinatesRead;
}

// �����ܣ���ȡ�ڵ㲢����ͼ
bool GraphFileIO::readNodesAndBuildGraph(Graph& graph, const char* filename) {
    std::printf("��ʼ���ļ���ȡ�ڵ�����: %s\n", filename);

    // ���ļ�
    FILE* file = nullptr;
    errno_t err = fopen_s(&file, filename, "r");
    if (err != 0 || file == nullptr) {
        std::fprintf(stderr, "�����޷����ļ� %s��������: %d\n", filename, err);
        return false; // ���ʵ��Ĵ�����
    }

    // �������������ڴ�
    double* xCoords = new double[MAX_NODES];
    double* yCoords = new double[MAX_NODES];

    if (xCoords == nullptr || yCoords == nullptr) {
        std::fprintf(stderr, "�����ڴ����ʧ��\n");
        std::fclose(file);
        delete[] xCoords;
        delete[] yCoords;
        return false;
    }

    int vertexCount = 0;
    int coordinatesRead = 0;
    bool success = false;

    try {
        // ��ȡ��������
        int fileVertexCount = readVertexCount(file, filename);
        if (fileVertexCount <= 0) {
            throw std::runtime_error("��Ч�Ķ�������");
        }

        std::printf("�ļ�������������: %d\n", fileVertexCount);

        // 使用Graph对象的实际大小作为顶点数量，确保与MainWindow中创建的Graph对象一致
        vertexCount = graph.getVertices();
        std::printf("实际使用的顶点数量: %d\n", vertexCount);

        // 检查文件中的顶点数量是否与Graph对象的大小一致
        if (fileVertexCount != vertexCount) {
            char buffer[100];
            sprintf_s(buffer, sizeof(buffer), "警告: 文件中的顶点数量(%d)与预期数量(%d)不一致，将使用预期数量",
                fileVertexCount, vertexCount);
            std::fprintf(stderr, "%s\n", buffer);
        }

        // ��ȡ����
        coordinatesRead = readCoordinates(file, vertexCount, xCoords, yCoords, filename);
        if (coordinatesRead != vertexCount) {
            std::fprintf(stderr, "���棺���� %d �����꣬���ɹ���ȡ %d ��\n", vertexCount, coordinatesRead);
            vertexCount = coordinatesRead;  // ʹ��ʵ�ʶ�ȡ������
        }

        std::printf("�ɹ���ȡ %d ���ڵ������\n", vertexCount);

        // Ϊÿ�Խڵ㴴����
        int edgesAdded = 0;
        int skippedCount = 0;

        for (int i = 0; i < vertexCount; i++) {
            // 保存节点坐标到Graph对象
            graph.setNodeCoordinates(i, xCoords[i], yCoords[i]);
            
            for (int j = i + 1; j < vertexCount; j++) {
                double distance = calculateDistance(xCoords[i], yCoords[i], xCoords[j], yCoords[j]);

                if (distance < 0 || std::isnan(distance) || std::isinf(distance)) {
                    std::fprintf(stderr, "���棺�ڵ� %d �� %d �ľ��������Ч: %.2f������\n", i, j, distance);
                    skippedCount++;
                    continue;
                }

                // ��������Ϊ����Ȩ��
                int weight = static_cast<int>(distance + 0.5);

                // ���ӱߵ�ͼ��
                graph.addEdge(i, j, weight);
                edgesAdded++;
            }
        }

        std::printf("ͼ������ɡ��ɹ����� %d ���ߣ����� %d ����Ч��\n", edgesAdded, skippedCount);
        success = true;

    }
    catch (const std::exception& e) {
        std::fprintf(stderr, "�����ļ�ʱ��������: %s\n", e.what());
        success = false;
    }

    // ������Դ
    std::fclose(file);
    delete[] xCoords;
    delete[] yCoords;

    return success;
}

// ���ļ��ȡ��������
int GraphFileIO::readVertexCountOnly(const char* filename) {
    FILE* file = nullptr;
    errno_t err = fopen_s(&file, filename, "r");
    if (err != 0 || file == nullptr) {
        std::fprintf(stderr, "�����޷����ļ� %s��������: %d\n", filename, err);
        return -1;
    }

    int vertexCount = -1;

    try {
        vertexCount = readVertexCount(file, filename);
    }
    catch (const std::exception& e) {
        std::fprintf(stderr, "���ļ��ȡ��������ʱ��������: %s\n", e.what());
        vertexCount = -1;
    }

    std::fclose(file);
    return vertexCount;
}

// �ļ���֤
bool GraphFileIO::validateFile(const char* filename) {
    std::printf("��֤�ļ���ʽ: %s\n", filename);

    FILE* file = nullptr;
    errno_t err = fopen_s(&file, filename, "r");
    if (err != 0 || file == nullptr) {
        std::fprintf(stderr, "�����޷����ļ� %s��������: %d\n", filename, err);
        return false; // ���ʵ��Ĵ�����
    }

    bool isValid = false;
    double* testX = nullptr;
    double* testY = nullptr;

    try {
        int vertexCount = readVertexCount(file, filename);
        if (vertexCount <= 0) {
            throw std::runtime_error("��Ч�Ķ�������");
        }

        // �����������
        testX = new double[vertexCount];
        testY = new double[vertexCount];

        // ���Զ�ȡǰ����������֤��ʽ
        int coordsToRead = (vertexCount < 5) ? vertexCount : 5;
        int coordsRead = readCoordinates(file, coordsToRead, testX, testY, filename);

        if (coordsRead != coordsToRead) {
            throw std::runtime_error("�����ȡ����������Ԥ��");
        }

        std::printf("�ļ���ʽ��֤ͨ������������: %d\n", vertexCount);
        isValid = true;

    }
    catch (const std::exception& e) {
        std::fprintf(stderr, "�ļ���ʽ��֤ʧ��: %s\n", e.what());
        isValid = false;
    }

    std::fclose(file);
    delete[] testX;
    delete[] testY;

    return isValid;
}