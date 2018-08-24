#pragma once

#include <cstdint>
#include <cassert>
#include <algorithm>
#include <cmath>

namespace sagl {


template <typename T>
class Vec2
{
public:
    T x() const
    {
        return m_x;
    }

    T y() const
    {
        return m_y;
    }

    void x(T x)
    {
        m_x = x;
    }

    void y(T y)
    {
        m_y = y;
    }

    void set( T px, T py )
    {
        x(px);
        y(py);
    }

    Vec2<T>& operator+=(const Vec2<T>& other )
    {
        m_x += other.x();
        m_y += other.y();
        return *this;
    }

private:
    T m_x = 0 ;
    T m_y = 0 ;

};


template <typename T>
class Rect
{
public:
    T x() const
    {
        return m_position.x();
    }

    T y() const
    {
        return m_position.y();
    }

    T width() const
    {
        return m_size.x();
    }

    T height() const
    {
        return m_size.y();
    }

    T left() const
    {
        return x();
    }

    T right() const
    {
        return left() + width();
    }

    T top() const
    {
        return y();
    }

    T bottom() const
    {
        return top() + height();
    }

    Vec2<T>& size()
    {
        return m_size;
    }

    Vec2<T>& position()
    {
        return m_position;
    }

    void set(T x, T y, T w, T h)
    {
        m_position.set(x, y);
        m_size.set(w, h);
    }

private:
    Vec2<T> m_position;
    Vec2<T> m_size;

};


template<typename T>
class Circle
{
public:
    Circle( T cx, T cy, T radius )
    {
        m_radius = radius;
        m_center.set(cx, cy);
    }

    Vec2<T>& position()
    {
        return m_center;
    }

    const Vec2<T>& position() const
    {
        return m_center;
    }

    void radius(T new_radius)
    {
        m_radius = new_radius;
    }

    T radius() const
    {
        return m_radius;
    }

    T left() const
    {
        return m_center.x() - radius();
    }

    T right() const
    {
        return m_center.x() + radius();
    }

    T top() const
    {
        return m_center.y() - radius();
    }

    T bottom() const
    {
        return m_center.y() + radius();
    }

private:
    Vec2<T> m_center;
    T m_radius;

};

template <typename T>
bool circle_inside_rect(const Circle<T>& c, const Rect<T>& r)
{
    return c.left() >= r.left() && c.right()  <= r.right() &&
           c.top()  >= r.top()  && c.bottom() <= r.bottom();
}

template <typename T>
bool circle_collides_with_rect( const Circle<T>& c, const Rect<T>& r)
{
    // Solution taken from: https://yal.cc/rectangle-circle-intersection-test/
    float dx, dy, cx, cy;
    cx = c.position().x();
    cy = c.position().y();
    dx = cx - std::max(r.x(), std::min(cx, r.x() + r.width()));
    dy = cy - std::max(r.y(), std::min(cy, r.y() + r.height()));
    return (dx * dx + dy * dy) < (c.radius() * c.radius());
};


template <typename T, size_t Cols, size_t Rows>
class Matrix
{
public:
    Matrix()
    {
        std::fill(m_data, m_data + Cols * Rows, 0);
    }

    T get(size_t col, size_t row) const
    {
        assert(col < Cols && row < Rows);
        return m_data[row * Cols + col];
    }

    void set(size_t col, size_t row,T value)
    {
        assert(col < Cols && row < Rows);
        m_data[row * Cols + col] = value;
    }

    const T* data() const
    {
        return m_data;
    }

    template <size_t Cols2, size_t Rows2>
    Matrix dot(const Matrix<T, Cols2, Rows2>& other)
    {
        assert(Cols == Rows2);
        Matrix m;
        for( int i = 0; i < Rows; i++ )
        {
            for( int j = 0; j < Cols2; j++ )
            {
                m.set(i, j, 0);
            }
        }
        for( int i = 0; i < Rows; i++ )
        {
            for( int j = 0; j < Cols2; j++ )
            {
                for( int k = 0; k < Cols; k++ )
                {
                    m.set(i, j, this->get(i, k) * other.get(k, j));
                }
            }
        }
        return m;
    }

private:
    T m_data[Cols * Rows];

};


template <typename T, size_t C1, size_t R1, size_t C2, size_t R2>
Matrix<T, R1, C2> operator*( const Matrix<T, C1, R1>& mA, const Matrix<T, C2, R2>& mB )
{
    assert(C1 == R2);
    Matrix<T, R1, C2> m;
    for( int i = 0; i < R1; i++ )
    {
        for( int j = 0; j < C2; j++ )
        {
            m.set(i, j, 0);
            for( int k = 0; k < C1; k++ )
            {
                m.set(i, j, m.get(i, j) + mA.get(i, k) * mB.get(k, j));
            }
        }
    }
    return m;
}


template <typename T>
class Matrix4x4 : public Matrix<T, 4, 4>
{
public:

    void setRow(size_t row, T cell0, T cell1, T cell2, T cell3)
    {
        Matrix<T, 4, 4>::set(0, row, cell0);
        Matrix<T, 4, 4>::set(1, row, cell1);
        Matrix<T, 4, 4>::set(2, row, cell2);
        Matrix<T, 4, 4>::set(3, row, cell3);
    }

    static Matrix4x4<T> MakeIdentity()
    {
        /**
         * 1 0 0 0
         * 0 1 0 0
         * 0 0 1 0
         * 0 0 0 1
         */
        Matrix4x4<T> m;
        m.setRow(0, 1, 0, 0, 0);
        m.setRow(1, 0, 1, 0, 0);
        m.setRow(2, 0, 0, 1, 0);
        m.setRow(3, 0, 0, 0, 1);
        return m;
    }

    static Matrix4x4<T> MakeTranslation(T x, T y)
    {
        /**
         * 1 0 0 X
         * 0 1 0 Y
         * 0 0 1 0
         * 0 0 0 1
         */
        Matrix4x4<T> m;
        m.setRow(0, 1, 0, 0, x);
        m.setRow(1, 0, 1, 0, y);
        m.setRow(2, 0, 0, 1, 0);
        m.setRow(3, 0, 0, 0, 1);
        return m;
    }

    static Matrix4x4<T> MakeOrtho(T bottom, T top, T left, T right, T near, T far)
    {
        Matrix4x4<T> m;
        m.setRow(0, 2.f / (right - left), 0, 0, 0);
        m.setRow(1, 0, 2.f / (top - bottom), 0, 0);
        m.setRow(2, 0, 0, -2.f / (far - near), 0);
        m.setRow(3, -(right + left) / (right - left), -(top + bottom) / (top - bottom), -(far + near) / (far - near), 1);
        return m;
    }

};


typedef Matrix4x4<float> Matrix4x4f;


}
