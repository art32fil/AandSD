#include <QtTest>

// add necessary includes here

class TestAvlTree : public QObject
{
  Q_OBJECT

public:
  TestAvlTree();
  ~TestAvlTree();

private slots:
  void test_case1();

};

TestAvlTree::TestAvlTree() {

}

TestAvlTree::~TestAvlTree() {

}

void TestAvlTree::test_case1() {

}

QTEST_APPLESS_MAIN(TestAvlTree)

#include "tst_testavltree.moc"
