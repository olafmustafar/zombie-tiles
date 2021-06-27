#include "gene.h"

#include <QRandomGenerator>

Gene::Gene(const double value, const double upper_bound, const double lower_bound)
    : value(value), upper_bound(upper_bound), lower_bound(lower_bound)
{}

void Gene::randomize()
{
    //    value = QRandomGenerator::global()->ge
}
