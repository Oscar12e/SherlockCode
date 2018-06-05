#include <time.h>
#include <stdlib.h>

#define NAME_GENOTYPE_MIN 0
#define NAME_GENOTYPE_MAX 14416

#define MAGICN_GENOTYPE_MIN 14417
#define MAGICN_GENOTYPE_MAX 26212

#define EXCEPTION_GENOTYPE_MIN 26213
#define EXCEPTION_GENOTYPE_MAX 42596

#define REPEATEDC_GENOTYPE_MIN 42597
#define REPEATEDC_GENOTYPE_MAX 65535


typedef struct Population Population, *ptrPopulation;
struct Population {
    int peopleAmount;
    unsigned short* genotypes;
    short mutationChance: 4;
};

Population* population_new(){
    Population *newPopulation = malloc(sizeof(Population));
    newPopulation->peopleAmount = 0;
    newPopulation->mutationChance = 12;
    newPopulation->genotypes = malloc(sizeof(unsigned short*));
    return newPopulation;
}


Population* addSubject(Population* pPopulation, int pType){
    unsigned short newGenotype;
    srand(time(NULL));

    switch(pType){
    case 1:
        newGenotype = rand() % (NAME_GENOTYPE_MAX + 1 - NAME_GENOTYPE_MIN) + NAME_GENOTYPE_MIN;
        break;
    case 2:
        newGenotype = rand() % (MAGICN_GENOTYPE_MAX + 1 - MAGICN_GENOTYPE_MIN) + MAGICN_GENOTYPE_MIN;
        break;
    case 3:
        newGenotype = rand() % (EXCEPTION_GENOTYPE_MAX + 1 - EXCEPTION_GENOTYPE_MIN) + EXCEPTION_GENOTYPE_MIN;
        break;
    default:
        newGenotype = rand() % (REPEATEDC_GENOTYPE_MAX + 1 - REPEATEDC_GENOTYPE_MIN) + REPEATEDC_GENOTYPE_MIN;
        break;

    }

    //Saves the new subject with a random genotype
    pPopulation->genotypes[pPopulation->peopleAmount] = newGenotype;
    //Updates the number of population
    pPopulation->peopleAmount++;
    return pPopulation;
}

Population* reproducePopulation(Population* pPopulation){
    return pPopulation;
}

unsigned short generateChild(unsigned short firstParent, unsigned short secondParent){
    return 0;
}
