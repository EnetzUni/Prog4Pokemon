#include "pokemonpresentacion.h"
#include "ui_pokemonpresentacion.h"

PokemonPresentacion::PokemonPresentacion(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PokemonPresentacion)
{
    ui->setupUi(this);
}

PokemonPresentacion::~PokemonPresentacion()
{
    delete ui;
}
