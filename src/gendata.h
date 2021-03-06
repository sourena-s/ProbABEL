/*
 * gendata.h
 *
 *  Created on: Mar 8, 2012
 *      Author: mkooyman
 *
 *
 * Copyright (C) 2009--2016 Various members of the GenABEL team. See
 * the SVN commit logs for more details.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA  02110-1301, USA.
 *
 */


#ifndef GENDATA_H_
#define GENDATA_H_
#include <string>
#include "fvlib/FileVector.h"

#include "eigen_mematrix.h"
#include "eigen_mematrix.cpp"


class gendata {
 public:
    unsigned int nsnps;
    unsigned int nids;
    unsigned int ngpreds;
    gendata();
    void mldose_line_to_matrix(const int k,
                               const char *all_numbers,
                               const int amount_of_numbers);

    void re_gendata(const char * fname,
                    const unsigned int insnps,
                    const unsigned int ingpreds,
                    const unsigned int npeople,
                    const unsigned int nmeasured,
                    const unsigned short int * allmeasured,
                    const int skipd,
                    const std::string * idnames);

    void re_gendata(const string filename,
                    const unsigned int insnps,
                    const unsigned int ingpreds,
                    const unsigned int npeople,
                    const unsigned int nmeasured,
                    const unsigned short int * allmeasured,
                    const std::string * idnames);

    void get_var(const int var, double * data) const;

    ~gendata();

    // MAKE THAT PRIVATE, ACCESS THROUGH GET_SNP
    // ANOTHER PRIVATE OBJECT IS A POINTER TO DATABELBASECPP
    // UPDATE SNP, ALL REGRESSION METHODS: ACCOUNT FOR MISSING
 private:
    /**
     * \brief Matrix containing the genotype data.
     *
     * - Nr of rows: nr. of individuals (usually phedata::nids).
     * - Nr. of columns: nr. of SNPs \f[\times\f] nr. of genomic
     *   predictors.
     */
    mematrix<double> G;

    /**
     * \brief Object of FileVector class that "links" to the genotype
     * information in the filevector file.
     *
     * Only used when reading genotype data from filevector files
     * (obviously).
     */
    AbstractMatrix * DAG;

    /**
     * \brief Array that masks individuals with incomplete phenotype
     * information.
     *
     * Only used when reading genotype data from filevector files.
     */

    unsigned short int * DAGmask;
};

#endif /* GENDATA_H_ */
