c *********************************************************************
c * DATA DE CRIACAO  : 11/09/2018                                     *
c * DATA DE MODIFICAO: 00/00/0000                                     *
c * ----------------------------------------------------------------- *
c * MONTASISTEMA : monta o sistema AX=B                               *
c * ----------------------------------------------------------------- *
c * Parametros de entrada:                                            *
c * ----------------------------------------------------------------- *
c * a      - nao definido                                             *
c * b      - nao definido                                             *
c * temp   - temperatura do passo anterior                            *
c * sQ     - fonte de calor                                           *
c * k      - coeficiente de conducao termica                          *
c * ro     - massa especidica                                         *
c * cp     - calor espefifico                                         *
c * dt     - delta t                                                  *
c * cc     - tipo de condicao de contorno                             * 
c         1 - Temperatuta                                             *
c         2 - fluxo                                                   *
c         3 - resfriamento de newton                                  *
c * ccv    - valor numerico da condicao de contorno                   *
c * dx     - delta x                                                  *
c * nCells - numero de celulas (elementos)                            * 
c * ----------------------------------------------------------------- *
c * Parametros de saida:                                              *
c * ----------------------------------------------------------------- *
c * a    - matriz de coefientes                                       *
c * b    - vetor b                                                    *
c * ----------------------------------------------------------------- *
c * OBS:                                                              *
c * ----------------------------------------------------------------- *
c *********************************************************************
      subroutine  montaSistema(a,b,temp,sQ,k,ro,cp,dt,cc,ccv,h,dx
     1                        ,nCells)
      implicit none
      integer cc(2),nCells,i
      real(8) a(nCells,*),b(*),k(*),ro(*),cp(*),temp(*),sQ(*)
      real(8) dt,ccv(2),dx,sP,sU,kf,tmp,h(2)
      real(8) aE,aW,aP0
c ... temperatura prescrita
      if(cc(1) .eq. 1) then
        aP0    = ro(1)*cp(1)*dx/dt
        sU     = (2.0d0*k(1)/dx)*ccv(1)
        sP     = -2.0d0*k(1)/dx
        kf     = (k(1)+k(2))*0.5d0
        aE     = kf/dx
c ... W
        a(1,1) = 0.0
c ... P
        a(1,2) = aP0 + aE - sP
c ... E
        a(1,3) = -aE
c ...
        b(1)   = sU + aP0*temp(1)
c ... fluxo prescrito
      else if(cc(1) .eq. 2) then
        aP0    = ro(1)*cp(1)*dx/dt
        sU     = -ccv(1)
        sP     = 0.0   
        kf     = (k(1)+k(2))*0.5d0
        aE     = kf/dx
c ... W
        a(1,1) = 0.0
c ... P
        a(1,2) = aP0 + aE - sP
c ... E
        a(1,3) = -aE
c ...
        b(1)   = sU + aP0*temp(1)
c ... lei de resfriamento de newton
      else if(cc(1) .eq. 3) then
        tmp    = 1.0d0 + (h(1)*2.0*dx)/k(1)
        tmp    = h(1)/tmp
        aP0    = ro(1)*cp(1)*dx/dt
        sU     = tmp*ccv(1)
        sP     = -tmp   
        kf     = (k(1)+k(2))*0.5d0
        aE     = kf/dx
c ... W
        a(1,1) = 0.0
c ... P
        a(1,2) = aP0 + aE - sP
c ... E
        a(1,3) = -aE
c ...
        b(1)   = sU + aP0*temp(1)

      endif
c .....................................................................

c ... temperatura prescrita
      if(cc(2) .eq. 1) then
        aP0    = ro(nCells)*cp(nCells)*dx/dt
        sU     = (2.0d0*k(nCells)/dx)*ccv(2)
        sP     = -2.0d0*k(nCells)/dx
        kf     = (k(nCells-1)+k(nCells))*0.5d0
        aW     = kf/dx
c ... W
        a(nCells,1) = -aW
c ... P
        a(nCells,2) = aP0 + aW - sP
c ... E
        a(nCells,3) = 0.0
c ...
        b(nCells)   = sU + aP0*temp(nCells)
c ... fluxo prescrito
      else if(cc(2) .eq. 2) then
        aP0    = ro(nCells)*cp(nCells)*dx/dt
        sU     = -ccv(2)
        sP     = 0.0
        kf     = (k(nCells-1)+k(nCells))*0.5d0
        aW     = kf/dx
c ... W
        a(nCells,1) = -aW
c ... P
        a(nCells,2) = aP0 + aW - sP
c ... E
        a(nCells,3) = 0.0
c ...
        b(nCells)   = sU + aP0*temp(nCells)
c ... lei de resfriamento de newton
      else if(cc(2) .eq. 3) then
        tmp    = 1.0d0 + (h(2)*2.0*dx)/k(nCells)
        tmp    = h(2)/tmp
        aP0    = ro(nCells)*cp(nCells)*dx/dt
        sU     = tmp*ccv(2)
        sP     = -tmp   
        kf     = (k(nCells-1)+k(nCells))*0.5d0
        aW     = kf/dx
c ... W
        a(nCells,1) = -aW
c ... P
        a(nCells,2) = aP0 + aW - sP
c ... E
        a(nCells,3) = 0.0
c ...
        b(nCells)   = sU + aP0*temp(nCells)
      endif
c .....................................................................

c ... loop nas celulas do interios
      do i = 2, nCells -1
        aP0    = ro(i)*cp(i)*dx/dt
c ... w 
        kf = (k(i-1) + k(i))*0.5d0
        aW = kf/dx  
c ...
        kf = (k(i) + k(i+1))*0.5d0
        aE = kf/dx  
c ... 
        a(i,1) = -aW 
        a(i,2) = aP0 + aW + aE 
        a(i,3) = -aE
c ... 
        b(i)   = aP0*temp(i)
      enddo
c .....................................................................
      return
      end
c *********************************************************************
