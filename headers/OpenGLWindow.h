#pragma once
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include "Point3D.h"
#include "Triangulation.h"

class QOpenGLTexture;
class QOpenGLShader;
class QOpenGLShaderProgram;

class QOpenGLPaintDevice;

class OpenGLWindow :public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    OpenGLWindow(const QColor& background, QMainWindow* parent);
    ~OpenGLWindow();
    void setSTLFile(const std::string& filePath);

public:
    void setData(const std::vector<Point3D>& vertices);
    void showDataOfFirstStl(std::string& filepath);
    void showDataOfSecondStl(std::string& filepath);
    void showIntersectedPart(std::string& filepath1, string& filepath2);
    void clearDataOfFirstStl();
    void clearDataOfSecondStl();
    void clearDataOfIntersectedArea(); 
    vector<GLfloat> verticesOfFirstStl();
    vector<GLfloat> verticesOfSecondStl();
    vector<GLfloat>verticesOfIntersectedPart();
    vector<GLfloat>colorOfFirstStl();
    vector<GLfloat>colorOfSecondStl();
    vector<GLfloat>colorOfIntersectedArea();
protected:
    void paintGL() override;
    void initializeGL() override;


private:
    void reset();
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
    void zoomIn();
    void zoomOut();


private:
    bool mAnimating = false;
    QOpenGLContext* mContext = nullptr;
    QOpenGLPaintDevice* mDevice = nullptr;

    QOpenGLShader* mVshader = nullptr;
    QOpenGLShader* mFshader = nullptr;
    QOpenGLShaderProgram* mProgram = nullptr;

    vector<Point3D> coordinatesOfFirstStl;
    vector<Point3D> coordinatesOfSecondStl;
    vector<Point3D>coordinatesOfIntersectedArea;

    QMatrix4x4 m_projectionMatrix;
    QMatrix4x4 m_viewMatrix;
    QMatrix4x4 m_modelMatrix;
    QQuaternion rotationAngle;
    QPoint lastPos;
    float scaleFactor = 1.0;

    int m_frame;


    QList<QVector3D> mVertices;
    QList<QVector3D> mNormals;
    QOpenGLBuffer mVbo;
    int mVertexAttr;
    int mNormalAttr;
    int mMatrixUniform;
    QColor mBackground;
    QMetaObject::Connection mContextWatchConnection;

    GLint m_posAttr = 0;
    GLint m_colAttr = 0;
    GLint m_matrixUniform = 0;
};
