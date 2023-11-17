#include <iostream>
using namespace std;

const int MAX_SIZE = 100; // 定义最大矩阵大小

// 定义稀疏矩阵的三元组表示
struct SparseMatrix {
    int row;   // 行数
    int col;   // 列数
    int value; // 非零元素的值
};

// 计算稀疏矩阵的转置
void transposeMatrix(SparseMatrix originalMatrix[],
                     SparseMatrix transposedMatrix[]);
// 计算稀疏矩阵的和
void addMatrices(SparseMatrix matrixA[], SparseMatrix matrixB[],
                 SparseMatrix resultMatrix[]);
// 计算稀疏矩阵的乘法
void multiplyMatrices(SparseMatrix matrixA[], SparseMatrix matrixB[],
                      SparseMatrix resultMatrix[]);
// 用于初始化稀疏矩阵
void convertToSparseMatrix(int arr[MAX_SIZE][MAX_SIZE], int n, int m,
                           SparseMatrix resultMatrix[]);
// 打印稀疏矩阵的三元组表示
void printSparseMatrix(const SparseMatrix matrix[]);

int main() {
    SparseMatrix matrixA[MAX_SIZE];
    SparseMatrix matrixB[MAX_SIZE];
    SparseMatrix transposedA[MAX_SIZE];
    SparseMatrix sumMatrix[MAX_SIZE];
    SparseMatrix productMatrix[MAX_SIZE];

    // 初始化 matrixA 和 matrixB
    int a[MAX_SIZE][MAX_SIZE] = {
        {1, 0, 3, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 1, 1}};
    int b[MAX_SIZE][MAX_SIZE] = {
        {3, 0, 0, 0}, {0, 4, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 2}};
    convertToSparseMatrix(a, 4, 4, matrixA);
    convertToSparseMatrix(b, 4, 4, matrixB);

    // 输出转置矩阵
    transposeMatrix(matrixA, transposedA);
    cout << "Transposed matrix A:" << endl;
    // 输出 transposedA
    printSparseMatrix(transposedA);

    // 输出矩阵相加
    addMatrices(matrixA, matrixB, sumMatrix);
    cout << "Sum of matrix A and B:" << endl;
    // 输出 sumMatrix
    printSparseMatrix(sumMatrix);

    // 输出矩阵相乘
    multiplyMatrices(matrixA, matrixB, productMatrix);
    cout << "Product of matrix A and B:" << endl;
    // 输出 productMatrix
    printSparseMatrix(productMatrix);

    return 0;
}

void transposeMatrix(SparseMatrix originalMatrix[],
                     SparseMatrix transposedMatrix[]) {
    // 获取原矩阵的行数和列数
    int originalRows = originalMatrix[0].row;
    int originalCols = originalMatrix[0].col;

    // 初始化转置矩阵的行数、列数和非零元素个数
    transposedMatrix[0].row = originalCols;
    transposedMatrix[0].col = originalRows;
    transposedMatrix[0].value = originalMatrix[0].value;

    int colCount[MAX_SIZE] = {0}; // 记录每列的非零元素个数

    // 计算每列的非零元素个数
    for (int i = 1; i <= originalMatrix[0].value; i++) {
        colCount[originalMatrix[i].col]++;
    }

    int colStart[MAX_SIZE] = {0}; // 记录每列的起始位置

    // 计算每列的起始位置
    for (int i = 2; i <= originalCols; i++) {
        colStart[i] = colStart[i - 1] + colCount[i - 1];
    }

    // 对原矩阵的每个非零元素进行转置
    for (int i = 1; i <= originalMatrix[0].value; i++) {
        int j = colStart[originalMatrix[i].col] + 1;
        transposedMatrix[j].row = originalMatrix[i].col;
        transposedMatrix[j].col = originalMatrix[i].row;
        transposedMatrix[j].value = originalMatrix[i].value;
        colStart[originalMatrix[i].col]++;
    }
}

void addMatrices(SparseMatrix matrixA[], SparseMatrix matrixB[],
                 SparseMatrix resultMatrix[]) {
    // 检查两个矩阵的维度是否相同
    if (matrixA[0].row != matrixB[0].row || matrixA[0].col != matrixB[0].col) {
        cout << "Matrix dimensions do not match for addition." << endl;
        return;
    }

    // 初始化结果矩阵的行数、列数和非零元素个数
    resultMatrix[0].row = matrixA[0].row;
    resultMatrix[0].col = matrixA[0].col;
    resultMatrix[0].value = 0;

    int a = 1, b = 1, resultIndex = 1;

    // 从头开始遍历两个矩阵，执行矩阵加法
    while (a <= matrixA[0].value && b <= matrixB[0].value) {
        int rowA = matrixA[a].row;
        int colA = matrixA[a].col;
        int valueA = matrixA[a].value;
        int rowB = matrixB[b].row;
        int colB = matrixB[b].col;
        int valueB = matrixB[b].value;

        if (rowA < rowB || (rowA == rowB && colA < colB)) {
            resultMatrix[resultIndex].row = rowA;
            resultMatrix[resultIndex].col = colA;
            resultMatrix[resultIndex].value = valueA;
            a++;
        } else if (rowA > rowB || (rowA == rowB && colA > colB)) {
            resultMatrix[resultIndex].row = rowB;
            resultMatrix[resultIndex].col = colB;
            resultMatrix[resultIndex].value = valueB;
            b++;
        } else {
            // 在相同位置的元素相加
            resultMatrix[resultIndex].row = rowA;
            resultMatrix[resultIndex].col = colA;
            resultMatrix[resultIndex].value = valueA + valueB;
            a++;
            b++;
        }

        // 更新结果矩阵的非零元素个数
        if (resultMatrix[resultIndex].value != 0) {
            resultMatrix[0].value++;
        }

        resultIndex++;
    }

    // 处理可能剩余的元素
    while (a <= matrixA[0].value) {
        resultMatrix[resultIndex].row = matrixA[a].row;
        resultMatrix[resultIndex].col = matrixA[a].col;
        resultMatrix[resultIndex].value = matrixA[a].value;
        a++;
        resultIndex++;
        resultMatrix[0].value++;
    }

    while (b <= matrixB[0].value) {
        resultMatrix[resultIndex].row = matrixB[b].row;
        resultMatrix[resultIndex].col = matrixB[b].col;
        resultMatrix[resultIndex].value = matrixB[b].value;
        b++;
        resultIndex++;
        resultMatrix[0].value++;
    }
}

void multiplyMatrices(SparseMatrix matrixA[], SparseMatrix matrixB[],
                      SparseMatrix resultMatrix[]) {
    // 检查矩阵A的列数是否等于矩阵B的行数
    if (matrixA[0].col != matrixB[0].row) {
        cout << "Matrix dimensions do not allow multiplication." << endl;
        return;
    }

    // 初始化结果矩阵的行数、列数和非零元素个数
    resultMatrix[0].row = matrixA[0].row;
    resultMatrix[0].col = matrixB[0].col;
    resultMatrix[0].value = 0;

    int aStart[MAX_SIZE] = {0}; // 记录矩阵A每行的起始位置
    int bStart[MAX_SIZE] = {0}; // 记录矩阵B每列的起始位置

    int aCount[MAX_SIZE] = {0}; // 记录矩阵A每行的非零元素个数

    // 计算矩阵A每行的非零元素个数和起始位置
    for (int i = 1; i <= matrixA[0].value; i++) {
        aCount[matrixA[i].row]++;
    }

    aStart[1] = 1;

    for (int i = 2; i <= matrixA[0].row; i++) {
        aStart[i] = aStart[i - 1] + aCount[i - 1];
    }

    // 对矩阵A的每个非零元素进行遍历
    for (int i = 1; i <= matrixA[0].row; i++) {
        if (aCount[i] == 0) {
            continue;
        }

        for (int j = 1; j <= matrixB[0].col; j++) {
            int sum = 0;
            for (int k = 1; k <= matrixA[0].col; k++) {
                for (int aIndex = aStart[i]; aIndex < aStart[i] + aCount[i];
                     aIndex++) {
                    if (matrixA[aIndex].col == k) {
                        for (int bIndex = bStart[k];
                             bIndex < bStart[k] + matrixB[0].value; bIndex++) {
                            if (matrixB[bIndex].row == k) {
                                sum += matrixA[aIndex].value *
                                       matrixB[bIndex].value;
                            }
                        }
                    }
                }
            }

            if (sum != 0) {
                int resultIndex = resultMatrix[0].value + 1;
                resultMatrix[resultIndex].row = i;
                resultMatrix[resultIndex].col = j;
                resultMatrix[resultIndex].value = sum;
                resultMatrix[0].value++;
            }
        }
    }
}

void convertToSparseMatrix(int arr[MAX_SIZE][MAX_SIZE], int n, int m,
                           SparseMatrix resultMatrix[]) {
    int nonzeroCount = 0; // 非零元素的计数器

    // 初始化稀疏矩阵的行数、列数和非零元素个数
    resultMatrix[0].row = n;
    resultMatrix[0].col = m;
    resultMatrix[0].value = 0;

    // 遍历二维数组，找到非零元素并添加到稀疏矩阵中
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (arr[i][j] != 0) {
                nonzeroCount++;
                int resultIndex = resultMatrix[0].value + 1;
                resultMatrix[resultIndex].row = i;
                resultMatrix[resultIndex].col = j;
                resultMatrix[resultIndex].value = arr[i][j];
                resultMatrix[0].value++;
            }
        }
    }
}

void printSparseMatrix(const SparseMatrix matrix[]) {
    int rows = matrix[0].row;
    int cols = matrix[0].col;

    std::cout << "Sparse Matrix (Three-Tuple Representation):" << std::endl;
    std::cout << "Rows: " << rows << ", Columns: " << cols
              << ", Non-Zero Values: " << matrix[0].value << std::endl;
    std::cout << "Row\tColumn\tValue" << std::endl;

    for (int i = 1; i <= matrix[0].value; i++) {
        std::cout << matrix[i].row << "\t" << matrix[i].col << "\t"
                  << matrix[i].value << std::endl;
    }
}