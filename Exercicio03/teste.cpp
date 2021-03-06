#include <iostream>
#include <math.h>
using namespace std;

float module(float a, float b, float c)
{
  return sqrt(pow(a, 2) + pow(b, 2) + pow(c, 2));
}

void vetorial(float *vector1, float *vector2, float *vectorReturn)
{
  vectorReturn[0] = vector1[1] * vector2[2] - vector1[2] * vector2[1];
  vectorReturn[1] = vector1[2] * vector2[0] - vector1[0] * vector2[2];
  vectorReturn[2] = vector1[0] * vector2[1] - vector1[1] * vector2[0];
}

void calculate_zc(float *vector, float *vectorReturn)
{
  vectorReturn[0] = -1 * vector[0] / module(vector[0], vector[1], vector[2]);
  vectorReturn[1] = -1 * vector[1] / module(vector[0], vector[1], vector[2]);
  vectorReturn[2] = -1 * vector[2] / module(vector[0], vector[1], vector[2]);
}

void calculate_xc(float *vector1, float *vector2, float *vectorReturn)
{
  float v[3];

  vetorial(vector1, vector2, v);

  vectorReturn[0] = v[0] / module(v[0], v[1], v[2]);
  vectorReturn[1] = v[1] / module(v[0], v[1], v[2]);
  vectorReturn[2] = v[2] / module(v[0], v[1], v[2]);
}

void create_matrix_bt(float *vector1, float *vector2, float *b_t)
{
  float zc[3], xc[3], yc[3];

  calculate_zc(vector1, zc);
  calculate_xc(vector2, zc, xc);
  calculate_xc(zc, xc, yc);

  float bt[16] = {xc[0], yc[0], zc[0], 0.0f,
                  xc[1], yc[1], zc[1], 0.0f,
                  xc[2], yc[2], zc[2], 0.0f,
                  0.00f, 0.00f, 0.0f, 1.0f};

  int l;
  for (l = 0; l < 16; l++)
    b_t[l] = bt[l];
}

void calculateMatrix(float *m1, float *m2, float **matrix_view)
{
  float m[16];
  int i, j;
  for (i = 0, j = 0; j < 16; j++)
  {
    m[j] = m1[i] * m2[3 * i] + m1[i + 1] * m2[4 + 4 * i] + m1[i + 2] * m2[7 + 4 * i] + m1[i + 3] * m2[11 + 4 * i];
    cout << m1[i] << " " << m2[3 * i] << " " << m1[i + 1] << " " << m2[4 + 4 * i] << " " << m1[i + 2] << " " << m2[7 + 4 * i] << " " << m1[i + 3] << " " << m2[11 + 4 * i];
    cout << m[j] << " ";
    if (j % 4 == 0)
    {
      cout << endl;
      i++;
    }
  }
}

int main()
{
  float *b_array;
  float d[3]{0.1f, -0.1f, -1.1f};
  float u[3]{0.0f, 1.0f, 0.0f};
  float p[3]{-0.1f, 0.1f, 0.1f};

  float t_array[16] = {1.00f, 0.00f, 0.00f, 0.00f,
                       0.00f, 1.00f, 0.00f, 0.00f,
                       0.00f, 0.00f, 1.00f, 0.00f,
                       -p[0], -p[1], -p[2], 1.00f};
  float view[16];
  create_matrix_bt(d, u, b_array);
  int l = 0;
  for (l = 0; l < 16; l++)
    cout << b_array[l] << " " << endl;

  // calculateMatrix(b_array, t_array, view);
  // vetorial(d, a2, ax);

  return 0;
}