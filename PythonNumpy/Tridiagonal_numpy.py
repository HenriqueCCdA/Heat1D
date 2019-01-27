import numpy as np
import time as tm
"""
c **********************************************************************
c * Data de criacao    : 26/01/2019                                    *
c * Data de modificaco : 00/00/0000                                    *
c * ------------------------------------------------------------------ *
c * Subroutine tdma : resolucao de sistemas tridiagonais               *
c * ------------------------------------------------------------------ *
c * Parametros de entrada:                                             *
c * ------------------------------------------------------------------ *
c * a      - matriz                                                    *
c *     a(:,0) - diagonal inferior                                     *
c *     a(:,1) - diagonal princial                                     *
c *     a(:,2) - diagonal princial                                     * 
c * b(neq)   - vetor independente                                      *
c * x(neq)   - vetor independente                                      *
c * um(neq)  - arranjo auxilar                                         *
c * bm(neq)  - arranjo auxilar                                         *
c * neq      - numero de equacoes                                      *
c * ------------------------------------------------------------------ *
c * Parametros de saida:                                               *
c * ------------------------------------------------------------------ *
c * x(neq) - vetor solucao                                             *
c * l(*),d(*),u(*) e b - inalterados                                   *
c * ------------------------------------------------------------------ *
c * OBS:                                                               *
c * ------------------------------------------------------------------ *
c * | d1 u1  0  0  0 | |x1| |b1|                                       *
c * | l2 d2 u2  0  0 | |x2| |b2|                                       *
c * | 0  l3 d3 u3  0 |*|x3|=|b3|                                       *
c * | 0   0 l4 d4 u4 | |x4| |b4|                                       *
c * | 0   0  0 l5 d5 | |x5| |b5|                                       *
c *                                                                    *
c * l = [  0 l2 l3 l4 l5]                                              *
c * d = [ d1 d2 d3 d4 d5]                                              *
c * u = [ u1 u2 u3 u4  0]                                              *
c *                                                                    *
c * fonte: https://en.wikipedia.org/wiki/Tridiagonal_matrix_algorithm  *
c **********************************************************************
"""


def tdma_solver1_numpy(a, b0, x, nEq):

    l = np.array(a[:,0],dtype = float)
    d = np.array(a[:,1],dtype = float)
    u = np.array(a[:,2],dtype = float)
    b = np.array(b0,dtype = float)

    # ...
    u[0] /= d[0]
    b[0] /= d[0]
    for i in range(1, nEq-1):
        u[i] /= (d[i] - u[i-1]*l[i])
        b[i] = (b[i] - b[i-1]*l[i]) / (d[i] - u[i-1]*l[i])
    b[-1] = (b[-1] - b[-2]*l[-1]) / (d[-1] - u[-2]*l[-1])
    # .................................................................

    # ...
    x[-1] = b[-1]
    for i in range(nEq-2, -1, -1):
        x[i] = b[i] - u[i]*x[i+1]
    # .................................................................


"""
c **********************************************************************
c * Data de criacao    : 26/01/2019                                    *
c * Data de modificaco : 00/00/0000                                    * 
c * ------------------------------------------------------------------ *   
c * Subroutine tdma : resolucao de sistemas tridiagonais               *    
c * ------------------------------------------------------------------ * 
c * Parametros de entrada:                                             *
c * ------------------------------------------------------------------ * 
c * a      - matriz                                                    *
c *     a(:,0) - diagonal inferior                                     *
c *     a(:,1) - diagonal princial                                     *
c *     a(:,2) - diagonal princial                                     * 
c * b(neq)   - vetor independente                                      *
c * x(neq)   - vetor independente                                      *
c * um(neq)  - arranjo auxilar                                         *
c * bm(neq)  - arranjo auxilar                                         *
c * neq      - numero de equacoes                                      *
c * ------------------------------------------------------------------ * 
c * Parametros de saida:                                               *
c * ------------------------------------------------------------------ *
c * x(neq) - vetor solucao                                             *
c * l(*),d(*),u(*) e b - inalterados                                   *
c * ------------------------------------------------------------------ * 
c * OBS:                                                               *
c * ------------------------------------------------------------------ * 
c * | d1 u1  0  0  0 | |x1| |b1|                                       *
c * | l2 d2 u2  0  0 | |x2| |b2|                                       *
c * | 0  l3 d3 u3  0 |*|x3|=|b3|                                       *
c * | 0   0 l4 d4 u4 | |x4| |b4|                                       *
c * | 0   0  0 l5 d5 | |x5| |b5|                                       *  
c *                                                                    *
c * l = [  0 l2 l3 l4 l5]                                              *
c * d = [ d1 d2 d3 d4 d5]                                              *
c * u = [ u1 u2 u3 u4  0]                                              *
c *                                                                    *
c * fonte: https://www.cfd-online.com/                                 *
c *       Wiki/Tridiagonal_matrix_algorithm_-_TDMA_(Thomas_algorithm)  *
c **********************************************************************
"""


def tdma_solver2_numpy(a, b0, x, nEq):   

    l = np.array(a[:,0],dtype = float)
    d = np.array(a[:,1],dtype = float)
    u = np.array(a[:,2],dtype = float)
    b = np.array(b0,dtype = float)

    # ...
    u[0] /= d[0]
    b[0] /= d[0]
    for i in range(1, nEq-1):
        m = l[i]/d[i-1]
        d[i] -= m*u[i-1]
        b[i] -= m*b[i-1]
    # .................................................................

    # ...
    x[-1] = b[-1]/d[-1]
    for i in range(nEq-2, -1, -1):
        x[i] = (b[i] - u[i]*x[i+1])/d[i]
    # .................................................................

    # .................................................................

"""
c **********************************************************************
c * Data de criacao    : 26/01/2019                                    *
c * Data de modificaco : 00/00/0000                                    *
c * ------------------------------------------------------------------ *
c * Subroutine tdma : resolucao de sistemas tridiagonais               *
c * ------------------------------------------------------------------ *
c * Parametros de entrada:                                             *
c * ------------------------------------------------------------------ *
c * l(neq)   - diagonal inferior                                       *
c * d(neq)   - diagonal principal                                      *
c * u(neq)   - diagonal superio                                        *
c * b(neq)   - vetor independente                                      *
c * x(neq)   - vetor independente                                      *
c * um(neq)  - arranjo auxilar                                         *
c * bm(neq)  - arranjo auxilar                                         *
c * neq      - numero de equacoes                                      *
c * ------------------------------------------------------------------ *
c * Parametros de saida:                                               *
c * ------------------------------------------------------------------ *
c * x(neq) - vetor solucao                                             *
c * l(*),d(*),u(*) e b - inalterados                                   *
c * ------------------------------------------------------------------ *
c * OBS:                                                               *
c * ------------------------------------------------------------------ *
c * | d1 u1  0  0  0 | |x1| |b1|                                       *
c * | l2 d2 u2  0  0 | |x2| |b2|                                       *
c * | 0  l3 d3 u3  0 |*|x3|=|b3|                                       *
c * | 0   0 l4 d4 u4 | |x4| |b4|                                       *
c * | 0   0  0 l5 d5 | |x5| |b5|                                       *
c *                                                                    *
c * l = [  0 l2 l3 l4 l5]                                              *
c * d = [ d1 d2 d3 d4 d5]                                              *
c * u = [ u1 u2 u3 u4  0]                                              *
c *                                                                    *
c * fonte: https://en.wikipedia.org/wiki/Tridiagonal_matrix_algorithm  *
c **********************************************************************
"""


def tdma_solver3_numpy(l, d, u, b0, x, nEq):

    b = np.array(b0,dtype = float)

    # ...
    u[0] /= d[0]
    b[0] /= d[0]
    for i in range(1, nEq-1):
        u[i] /= (d[i] - u[i-1]*l[i])
        b[i] = (b[i] - b[i-1]*l[i]) / (d[i] - u[i-1]*l[i])
    b[-1] = (b[-1] - b[-2]*l[-1]) / (d[-1] - u[-2]*l[-1])
    # .................................................................

    # ...
    x[-1] = b[-1]
    for i in range(nEq-2, -1, -1):
        x[i] = b[i] - u[i]*x[i+1]
    # .................................................................
