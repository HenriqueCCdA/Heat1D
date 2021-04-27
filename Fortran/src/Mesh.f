c *********************************************************************
c * DATA DE CRIACAO  : 16/09/2018                                     *
c * DATA DE MODIFICAO: 10/10/2018                                     *
c * ----------------------------------------------------------------- *
c * NODALINTPERPOL: interla os valores das celulas para o no          *
c * ----------------------------------------------------------------- *
c * Parametros de entrada:                                            *
c * ----------------------------------------------------------------- *
c * cells- conetividade nodal das celulas                             *
c * cc     - tipo de condicao de contorno                             * 
c         1 - Temperatuta                                             *
c         2 - fluxo                                                   *
c         3 - resfriamento de newton                                  *
c * ccv    - valor numerico da condicao de contorno                   *
c * cellTemp - valores nas celulas                                    *
c * nodeTemp - nao definido                                           *
c * nCells   - numero de celulas                                      *
c * nPoints  - numero de pontos                                       *
c * ----------------------------------------------------------------- *
c * Parametros de saida:                                              *
c * ----------------------------------------------------------------- *
c * nodeTemp - valores nos pontos                                     *
c * ----------------------------------------------------------------- *
c * OBS:                                                              *
c * ----------------------------------------------------------------- *
c *********************************************************************
      subroutine nodalInterpol(cells,cc,ccv,cellTemp,nodeTemp,nCells
     .                        ,nPoints)
      implicit none
      integer nCells,nPoints,cells(2,*),cc(2),i
      real(8) cellTemp(*),nodeTemp(*),no1,no2,tmp,ccv(2)
c ...
      nodeTemp(1:nPoints) = 0.d0
c ...
      do i = 1, nCells
        no1           = cells(1,i)
        no2           = cells(2,i)
        tmp           = cellTemp(i)
        nodeTemp(no1) = nodeTemp(no1) + tmp
        nodeTemp(no2) = nodeTemp(no2) + tmp
      enddo
c .....................................................................      
c
c ...   
      do i = 2, nPoints - 1
        nodeTemp(i) = nodeTemp(i)*0.5d0
      enddo
c .....................................................................
c
c ...
      if (cc(1) .eq. 1) nodeTemp(1)       = ccv(1)
      if (cc(2) .eq. 1) nodeTemp(nPoints) = ccv(2)
c .....................................................................
      return
      end
c .....................................................................
c *********************************************************************
c
c *********************************************************************
c * DATA DE CRIACAO  : 11/09/2018                                     *
c * DATA DE MODIFICAO: 00/00/0000                                     *
c * ----------------------------------------------------------------- *
c * GRID: gera o gride pontos                                         *
c * ----------------------------------------------------------------- *
c * Parametros de entrada:                                            *
c * ----------------------------------------------------------------- *
c * x    - nao definido                                               *
c * xc   - nao definido                                               *
c * cell - nao definido                                               *
c * comp - comprimento da barra                                       *
c * nPoint - numero de pontos                                         *
c * nDiv   - numero de divisoes (elementos)                           *
c * ----------------------------------------------------------------- *
c * Parametros de saida:                                              *
c * ----------------------------------------------------------------- *
c * x    - cordenada dos pontos                                       *
c * xc   - cordenadas dos centro dos elmentos                         *
c * cell - conectividade nodais do elementos                          *
c * ----------------------------------------------------------------- *
c * OBS:                                                              *
c * ----------------------------------------------------------------- *
c *********************************************************************
      subroutine grid(x,xc,cell,comp,dx,nCell,nPoints,nDiv)  
      implicit none
      integer i,nCell,nPoints,nDiv,cell(2,*)
      real(8) dx,comp
      real(8) x(*),xc(*)
c ... gerando cordenadas nodais
      dx   = comp/nDiv
      x(1) = 0.0d0
      do i = 2, nPoints - 1
        x(i) = x(i-1) + dx
      enddo
      x(nPoints) = comp
c .....................................................................
c
c ... gerando conectividade nodais
      do i = 1, nCell
        cell(1,i) = i 
        cell(2,i) = i + 1
        xc(i)     = (x(i+1)+x(i))*0.5d0
      enddo
c .....................................................................
c
c ...
      return
      end
c .......................................................................            
c *********************************************************************