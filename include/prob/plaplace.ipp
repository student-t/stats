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
 * cdf of the univariate Laplace distribution
 */

//
// single input

template<typename T>
statslib_constexpr
T
plaplace_int(const T x, const T sigma_par)
{
    return ( T(0.5) + T(0.5)*gcem::sgn(x)*(T(1.0) - stmath::exp(-stmath::abs(x) / sigma_par)) );
}

template<typename T>
statslib_constexpr
T
plaplace(const T x, const T mu_par, const T sigma_par, const bool log_form)
{
    return ( log_form == true ? stmath::log(plaplace_int(x - mu_par,sigma_par)) :
                                plaplace_int(x - mu_par,sigma_par) );
}

//
// matrix/vector input

template<typename Ta, typename Tb, typename Tc>
statslib_inline
void
plaplace_int(const Ta* __stats_pointer_settings__ vals_in, const Tb mu_par, const Tb sigma_par, const bool log_form, 
                   Tc* __stats_pointer_settings__ vals_out, const uint_t num_elem)
{
#ifdef STATS_USE_OPENMP
    #pragma omp parallel for
#endif
    for (uint_t j=0U; j < num_elem; j++)
    {
        vals_out[j] = plaplace(vals_in[j],mu_par,sigma_par,log_form);
    }
}

#ifdef STATS_USE_ARMA
template<typename Ta, typename Tb, typename Tc>
statslib_inline
ArmaMat<Tc>
plaplace(const ArmaMat<Ta>& X, const Tb mu_par, const Tb sigma_par, const bool log_form)
{
    ArmaMat<Tc> mat_out(X.n_rows,X.n_cols);

    plaplace_int<Ta,Tb,Tc>(X.memptr(),mu_par,sigma_par,log_form,mat_out.memptr(),mat_out.n_elem);

    return mat_out;
}
#endif

#ifdef STATS_USE_BLAZE
template<typename Ta, typename Tb, typename Tc, bool To>
statslib_inline
BlazeMat<Tc,To>
plaplace(const BlazeMat<Ta,To>& X, const Tb mu_par, const Tb sigma_par, const bool log_form)
{
    BlazeMat<Tc,To> mat_out(X.rows(),X.columns());

    plaplace_int<Ta,Tb,Tc>(X.data(),mu_par,sigma_par,log_form,mat_out.data(),X.rows()*X.spacing());

    return mat_out;
}
#endif

#ifdef STATS_USE_EIGEN
template<typename Ta, typename Tb, typename Tc, int iTr, int iTc>
statslib_inline
EigMat<Tc,iTr,iTc>
plaplace(const EigMat<Ta,iTr,iTc>& X, const Tb mu_par, const Tb sigma_par, const bool log_form)
{
    EigMat<Tc,iTr,iTc> mat_out(X.rows(),X.cols());

    plaplace_int<Ta,Tb,Tc>(X.data(),mu_par,sigma_par,log_form,mat_out.data(),mat_out.size());

    return mat_out;
}
#endif
