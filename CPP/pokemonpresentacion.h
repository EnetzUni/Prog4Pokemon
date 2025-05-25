#ifndef POKEMONPRESENTACION_H
#define POKEMONPRESENTACION_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class PokemonPresentacion;
}
QT_END_NAMESPACE

class PokemonPresentacion : public QMainWindow
{
    Q_OBJECT

public:
    PokemonPresentacion(QWidget *parent = nullptr);
    ~PokemonPresentacion();

private:
    Ui::PokemonPresentacion *ui;
};
#endif // POKEMONPRESENTACION_H
