c **********************************************************************
c * Data de criacao    : 27/08/2018                                    *
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
      subroutine tdma_solver1(l,d,u,b,x,um,bm,neq)
      implicit none
      integer i,neq
      real*8 l(*), d(*), u(*), b(*), x(*)
      real*8 um(*),bm(*)     
c ...
      do i = 1, neq
        um(i) = u(i)
        bm(i) = b(i)
      enddo
c .....................................................................
c
c ...                 
      um(1) = um(1)/d(1)
      bm(1) = bm(1)/d(1)
      do i = 2, neq - 1
        um(i) = um(i)/(d(i) - um(i-1)*l(i))
        bm(i) = (bm(i) - bm(i-1)*l(i)) / ( d(i) - um(i-1)*l(i))
      enddo
      bm(i) = (bm(i) - bm(i-1)*l(i)) / ( d(i) - um(i-1)*l(i))
c .....................................................................
c
c ...
      x(neq) = bm(neq)
      do i = neq-1, 1, -1
        x(i) = bm(i) - um(i)*x(i+1)
      enddo  
c ......................................................................
c
c ...
      return
      end
c **********************************************************************
c
c
c **********************************************************************
c * Data de criacao    : 27/08/2018                                    *
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
c * fonte: https://www.cfd-online.com/                                 *
c *       Wiki/Tridiagonal_matrix_algorithm_-_TDMA_(Thomas_algorithm)  *
c **********************************************************************
      subroutine tdma_solver2(l,d,u,b,x,dm,bm,neq)
      implicit none
      integer i,neq
      real*8 l(*), d(*), u(*), b(*), x(*)
      real*8 dm(*),bm(*),m     
c ...
      do i = 1, neq
        dm(i) = d(i)
        bm(i) = b(i)
      enddo
c .....................................................................
c
c ...                 
      do i = 2, neq
        m     = l(i)/dm(i-1)
        dm(i) = dm(i) - m*u(i-1)
        bm(i) = bm(i) - m*bm(i-1)
      enddo
c .....................................................................
c
c ...
      x(neq) = bm(neq)/dm(neq)
      do i = neq-1, 1, -1
        x(i) = (bm(i) - u(i)*x(i+1))/dm(i)
      enddo  
c ......................................................................
c
c ...
      return
      end
c **********************************************************************
