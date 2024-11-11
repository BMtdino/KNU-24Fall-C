#include <stdio.h>

typedef struct {
    float x;
    float y;
    float z;
} Vector3D;

// 두 벡터의 합 계산 함수
Vector3D addVectors(Vector3D v1, Vector3D v2) {
    Vector3D result = { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
    return result;
}

// 두 벡터의 차 계산 함수
Vector3D subtractVectors(Vector3D v1, Vector3D v2) {
    Vector3D result = { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
    return result;
}

// 두 벡터의 내적 계산 함수
float dotProduct(Vector3D v1, Vector3D v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

// 두 벡터의 외적 계산 함수
Vector3D crossProduct(Vector3D v1, Vector3D v2) {
    Vector3D result = {
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x
    };
    return result;
}

int main() {
    Vector3D v1, v2;

    Vector3D sum = addVectors(v1, v2);
    Vector3D diff = subtractVectors(v1, v2);
    float dot = dotProduct(v1, v2);
    Vector3D cross = crossProduct(v1, v2);

    printf("첫번째 벡터(x, y, z) : %.0f, %.0f, %.0f\n", v1.x, v1.y, v1.z);
    printf("v1 + v2 = (%.2f, %.2f, %.2f)\n", sum.x, sum.y, sum.z);
    printf("v1 - v2 = (%.2f, %.2f, %.2f)\n", diff.x, diff.y, diff.z);
    printf("Dot product = %.2f\n", dot);
    printf("Cross product = (%.2f, %.2f, %.2f)\n", cross.x, cross.y, cross.z);

    return 0;
}
