#pragma once
#include <math.h>
#include <stdint.h>

class GMatrix {
    float m[3][3];

   public:
    GMatrix() {
        reset();
    }

    // ================ FABRIC ================

    // единичная матрица
    static GMatrix identity() {
        return GMatrix();
    }

    // матрица поворота
    static GMatrix rotation(float rad) {
        GMatrix mx;
        float c = cosf(rad), s = sinf(rad);
        mx[0][0] = c, mx[0][1] = -s;
        mx[1][0] = s, mx[1][1] = c;
        return mx;
    }

    // матрица сдвига
    static GMatrix translation(float dx, float dy) {
        GMatrix mx;
        mx[0][2] = dx;
        mx[1][2] = dy;
        return mx;
    }

    // матрица масштабирования
    static GMatrix scaling(float sx, float sy) {
        GMatrix mx;
        mx[0][0] = sx;
        mx[1][1] = sy;
        return mx;
    }

    // матрица масштабирования
    static GMatrix scaling(float sxy) {
        GMatrix mx;
        mx[0][0] = mx[1][1] = sxy;
        return mx;
    }

    // ================ GET ================

    // доступ как matrix[0][0]
    inline float* operator[](uint8_t i) {
        return m[i];
    }
    inline const float* operator[](uint8_t i) const {
        return m[i];
    }

    // создать копию
    GMatrix copy() const {
        return *this;
    }

    // обратная матрица
    GMatrix inverted() const {
        float det =
            m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) -
            m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) +
            m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);

        if (fabs(det) < 1e-6) return GMatrix();

        float invDet = 1.0f / det;

        GMatrix inv;
        inv[0][0] = (m[1][1] * m[2][2] - m[1][2] * m[2][1]) * invDet;
        inv[0][1] = -(m[0][1] * m[2][2] - m[0][2] * m[2][1]) * invDet;
        inv[0][2] = (m[0][1] * m[1][2] - m[0][2] * m[1][1]) * invDet;

        inv[1][0] = -(m[1][0] * m[2][2] - m[1][2] * m[2][0]) * invDet;
        inv[1][1] = (m[0][0] * m[2][2] - m[0][2] * m[2][0]) * invDet;
        inv[1][2] = -(m[0][0] * m[1][2] - m[0][2] * m[1][0]) * invDet;

        inv[2][0] = (m[1][0] * m[2][1] - m[1][1] * m[2][0]) * invDet;
        inv[2][1] = -(m[0][0] * m[2][1] - m[0][1] * m[2][0]) * invDet;
        inv[2][2] = (m[0][0] * m[1][1] - m[0][1] * m[1][0]) * invDet;

        return inv;
    }

    // транспонированная матрица
    GMatrix transposed() const {
        GMatrix t;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                t[i][j] = m[j][i];
        return t;
    }

    // умножение на другую матрицу
    GMatrix operator*(const GMatrix& other) const {
        GMatrix res;
        for (uint8_t row = 0; row < 3; row++) {
            for (uint8_t col = 0; col < 3; col++) {
                res[row][col] = 0;
                for (uint8_t k = 0; k < 3; k++) {
                    res[row][col] += m[row][k] * other[k][col];
                }
            }
        }
        return res;
    }

    // ================ DECOMPOSE ================
    struct Decomposed {
        float angle;   // угол в радианах
        float sx, sy;  // масштабы по осям
        float tx, ty;  // сдвиг по осям
    };

    // разложить на составляющие
    Decomposed decompose() const {
        Decomposed result;
        result.tx = m[0][2];
        result.ty = m[1][2];

        result.sx = sqrtf(m[0][0] * m[0][0] + m[1][0] * m[1][0]);
        result.sy = sqrtf(m[0][1] * m[0][1] + m[1][1] * m[1][1]);

        if (result.sx > 1e-6f) result.angle = atan2f(m[1][0], m[0][0]);
        else result.angle = 0.0f;

        return result;
    }

    // ================ MODIFY ================

    // умножить на другую матрицу
    GMatrix& mul(const GMatrix& other) {
        for (uint8_t row = 0; row < 3; ++row) {
            float r[3] = {m[row][0], m[row][1], m[row][2]};
            for (uint8_t col = 0; col < 3; ++col) {
                m[row][col] = r[0] * other.m[0][col] + r[1] * other.m[1][col] + r[2] * other.m[2][col];
            }
        }
        return *this;
    }
    GMatrix& operator*=(const GMatrix& other) {
        return mul(other);
    }

    // сделать единичной
    GMatrix& reset() {
        m[0][0] = 1, m[0][1] = 0, m[0][2] = 0;
        m[1][0] = 0, m[1][1] = 1, m[1][2] = 0;
        m[2][0] = 0, m[2][1] = 0, m[2][2] = 1;
        return *this;
    }

    // повернуть
    GMatrix& rotate(float rad) {
        return mul(rotation(rad));
    }

    // переместить
    GMatrix& translate(float dx, float dy) {
        return mul(translation(dx, dy));
    }

    // масштабировать
    GMatrix& scale(float sx, float sy) {
        return mul(scaling(sx, sy));
    }
    GMatrix& scale(float sxy) {
        return mul(scaling(sxy));
    }

    // транспонировать
    GMatrix& transpose() {
        for (uint8_t i = 0; i < 3; ++i) {
            for (uint8_t j = i + 1; j < 3; ++j) {
                float tmp = m[i][j];
                m[i][j] = m[j][i];
                m[j][i] = tmp;
            }
        }
        return *this;
    }

    // инвертировать
    GMatrix& invert() {
        return *this = inverted();
    }
};