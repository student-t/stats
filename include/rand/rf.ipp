/*################################################################################
  ##
  ##   Copyright (C) 2011-2018 Keith O'Hara
  ##
  ##   This file is part of the StatsLib C++ library.
  ##
  ##   Licensed under the Apache License, Version 2.0 (the "License");
  ##   you may not use this file except in compliance with the License.
  ##   You may obtain a copy of the License at
  ##
  ##       http://www.apache.org/licenses/LICENSE-2.0
  ##
  ##   Unless required by applicable law or agreed to in writing, software
  ##   distributed under the License is distributed on an "AS IS" BASIS,
  ##   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  ##   See the License for the specific language governing permissions and
  ##   limitations under the License.
  ##
  ################################################################################*/

/*
 * Sample from a F distribution
 */

template<typename T>
T
rf_int(const T df1_par, const T df2_par)
{
    const T X = rchisq(df1_par);
    const T Y = rchisq(df2_par);

    //
    
    return (df2_par / df1_par) * X / Y;
}

template<typename T>
return_t<T>
rf(const T df1_par, const T df2_par)
{
    return rf_int(return_t<T>(df1_par),return_t<T>(df2_par));
}

template<typename T>
void
rf_int(const T df1_par, const T df2_par, T* vals_out, const uint_t num_elem)
{
#ifdef STATS_USE_OPENMP
    #pragma omp parallel for
#endif
    for (uint_t j=0U; j < num_elem; j++)
    {
        vals_out[j] = rf(df1_par,df2_par);
    }
}

#ifdef STATS_WITH_MATRIX_LIB
template<typename mT, typename eT>
mT
rf(const uint_t n, const uint_t k, const eT df1_par, const eT df2_par)
{
    mT mat_out(n,k);

    rf_int(df1_par,df2_par,mat_ops::get_mem_ptr(mat_out),n*k);

    return mat_out;
}
#endif
