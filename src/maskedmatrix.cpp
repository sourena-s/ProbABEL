/*
 * maskedmatrix.cpp
 *
 *  Created on: May 22, 2012
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



#include <vector>
#include <algorithm>
#include "maskedmatrix.h"
#include "eigen_mematrix.h"
#include "eigen_mematrix.cpp"


masked_matrix::masked_matrix()
{
    length_of_mask = 0;
    masked_data = NULL;
}


masked_matrix::masked_matrix(mematrix<double> M) : matrix_original(M)
{
    masked_data = &matrix_original;
    mask_of_old = std::vector<bool> (M.nrow, false);
    length_of_mask = mask_of_old.size();
}


void masked_matrix::set_matrix(const mematrix<double> &M)
{
    matrix_original = M;
    masked_data = &matrix_original;
    mask_of_old = std::vector<bool> (M.nrow, false);
    length_of_mask = mask_of_old.size();
}


void masked_matrix::update_mask(std::vector<bool> newmask)
{
    // Find the number of non-masked entries in newmask
    int nmeasured = std::count(newmask.begin(), newmask.end(), 0);

    // Check update mask is the same as original matrix
    if (nmeasured == length_of_mask)
    {
        // Masked matrix is the same as original matrix
        masked_data = &matrix_original;
    }
    else
    {
        // Check update mask is the same as old matrix
        if (newmask == mask_of_old)
        {
            // New mask is the same as old matrix
            masked_data = &matrix_masked_data;
        }
        else
        {
            // New mask differs from old matrix and create new.
            mask_of_old = newmask;
            mask_symmetric(nmeasured);
            masked_data = &matrix_masked_data;
        }
    }
}


void masked_matrix::mask_symmetric(int nmeasured)
{
    // Mask a symmetric matrix: this matrix is always a square matrix and will
    // mask rows and columns. The result is always a square matrix
    matrix_masked_data.reinit(nmeasured, nmeasured);
    int i1 = 0, j1 = 0;

    for (int i = 0; i < length_of_mask; i++)
        if (mask_of_old[i] == 0)
        {
            j1 = 0;
            for (int j = 0; j < length_of_mask; j++)
                if (mask_of_old[j] == 0)
                {
                    //std::cout << "val" << i1 << " " << j1 << "\n";
                    matrix_masked_data.put(matrix_original.get(i, j), i1, j1);
                    j1++;
                }
            i1++;
        }
}
