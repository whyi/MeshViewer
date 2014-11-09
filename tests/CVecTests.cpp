#include <QString>
#include <QtTest>
#include "CVec.h"

class CVecTests : public QObject
{
  Q_OBJECT
  
public:
  CVecTests();
private Q_SLOTS:
  void ShouldDefaultToOriginWhenNoParameterPassed();
  void ShouldNormalizeItself();
};

CVecTests::CVecTests()
{
}

void CVecTests::ShouldDefaultToOriginWhenNoParameterPassed()
{
    CVec vec;
    QVERIFY2(vec.x() == 0.0, "X coordinate should be 0.0");
    QVERIFY2(vec.y() == 0.0, "Y coordinate should be 0.0");
    QVERIFY2(vec.z() == 0.0, "Z coordinate should be 0.0");
}

void CVecTests::ShouldNormalizeItself()
{
    CVec xVector(100,0,0);
    xVector.normalize();
    QVERIFY2(xVector.x() == 1.0, "X component should be normalize to 1.0");

    CVec yVector(0,100,0);
    yVector.normalize();
    QVERIFY2(yVector.y() == 1.0, "Y component should be normalize to 1.0");

    CVec zVector(0,0,100);
    zVector.normalize();
    QVERIFY2(zVector.z() == 1.0, "Z component should be normalize to 1.0");
}

QTEST_APPLESS_MAIN(CVecTests)

#include "CVecTests.moc"
