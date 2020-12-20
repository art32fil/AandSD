#include "currentcontrol.h"
#include "avltree.h"

#include <QApplication>

int main(int argc, char *argv[]) {
//  AvlTree<char>* avlt = new AvlTree<char>();

//  avlt->insert('b');
//  avlt->insert('g');
//  avlt->insert('a');
//  avlt->insert('f');
//  avlt->insert('h');
//  avlt->insert('e');

////  avlt.insert('k');
////  avlt.insert('m');
////  avlt.insert('q');
////  avlt.insert('w');
////  avlt.insert('r');
////  avlt.insert('t');

//  std::string dir("/home/mur/Programing/QtProjects/AaDS/AvlTreeCurrentControl/");
//  std::string fileName("graph");

//  // Создание файла с описанием графа
//  std::fstream dotFile("./" + fileName + "_main.gv", std::ios_base::out);



//  // Сохранение исходного дерева в файл
//  avlt->printDot(dotFile);

//  dotFile.close();

//  std::system(("dot -Tpng -o ./" + fileName + "_main.png ./" + fileName + "_main.gv").c_str());

//  delete avlt;

  QApplication a(argc, argv);
  CurrentControl w;
  w.show();
  return a.exec();
}
