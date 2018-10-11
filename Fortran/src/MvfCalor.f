c *********************************************************************
c * DATA DE CRIACAO  : 01/09/2018                                     *
c * DATA DE MODIFICAO: 00/00/0000                                     *
c * ----------------------------------------------------------------- *
c * heat: Programa de volume finitos para equacao do calor 1d         *
c * ----------------------------------------------------------------- *
c * ----------------------------------------------------------------- *
c * OBS:                                                              *
c * ----------------------------------------------------------------- *
c *********************************************************************      
      program heat
      implicit none
      include 'Time.fi'
      character(len=80) nameOut, dum, name
      real(8) lComp,dx,dt,ccv(2),t,temp0,h(2),prop(3)      
      integer nCells,nPoints,nDiv,i,j,cc(2),nStep
      integer, dimension(:,:), allocatable :: cells
      real(8), dimension(:), allocatable :: b,x,xc,cellTemp,nodeTemp,
     .                                      k,ro,cp,sQ
      real(8), dimension(:), allocatable :: ye
      real(8), dimension(:,:), allocatable :: a,aux
      integer nin  /11/
      integer nout1 /12/,nout2 /13/, nout3 /14/
c .....................................................................
c
c ...
      timeSolver = 0.d0
      timeSist   = 0.d0
      timeWres   = 0.d0
c .....................................................................
c
c ...
      call readfile(lComp,nDiv,dt,nStep,cc,ccv,h,temp0,prop,nameOut,nin)
c .....................................................................
c
c ....
      nCells  = nDiv
      nPoints = nDiv + 1
c .....................................................................
c
c ...
      allocate(b(nCells)       , x(nPoints), xc(nCells)
     1       , cellTemp(nCells), nodeTemp(nPoints)
     2       , k(nCells)       , ro(nCells), cp(nCells)
     3       , a(nCells,3)     , aux(nCells,2)
     4       , cells(2,nCells) , sQ(nCells), ye(nPoints))
c .....................................................................
c
c .... gera o gride
      call grid(x,xc,cells,lComp,dx,nCells,nPoints,nDiv)  
c ....................................................................
c
c ...
      t                  = 0.d0
      k(1:nCells)        = prop(1)
      ro(1:nCells)       = prop(2)
      cp(1:nCells)       = prop(3)
      cellTemp(1:nCells) = temp0
      sQ(1:nCells)       = 0.d0
c ....................................................................      
c
c ...
      name = trim(nameOut) // '_cell.out'
      open(unit=nout1,FILE=name)
      name = trim(nameOut) // '_node.out'
      open(unit=nout2,FILE=name)
c      name = trim(nameOut) // '_ex.out'
c      open(unit=nout3,FILE=name)
c ....................................................................
c
c ...
      call nodalInterpol(cells,cc,ccv,cellTemp,nodeTemp,nCells
     .                  ,nPoints)
c ...................................................................
c
c ...  escrita da coordenada do centroide
      time0 = get_wtime()
      call res(0,0.d0,xc,nCells,nout1)
      call res(0,0.d0,x,nPoints,nout2)
c      call res(0,0.d0,x,nPoints,nout3)
      timeWres = timeWres + get_wtime() - time0
c ...................................................................
c
c ...
      call solExt(x,ye,t,dsqrt(k(1)/ro(1)*cp(1)),lComp,nPoints)
c ...................................................................
c 
c ...  escrita da temperatura inicial
      time0 = get_wtime()
      call res(0,0.d0,cellTemp,nCells ,nout1)
      call res(0,0.d0,nodeTemp,nPoints,nout2)
c      call res(0,0.d0,ye      ,nPoints,nout3)
c      call derr(ye,nodeTemp,nPoints)
      timeWres = timeWres + get_wtime() - time0
c ...................................................................
c
c ...
      write(*,'(20a)')'Running ...'
c ...................................................................
c
c ...
      do j = 1, nStep
c
c ... 
c       write(*,'(a10,1x,i9)')'Step :', j
c       write(*,'(a10,1x,f9.4)')'Time(s) :',t
        t = t + dt
c ...................................................................
c
c ...
c       write(*,*)'Assembly of the matrix system :'
        time0 = get_wtime()
        call montaSistema(a,b,cellTemp,sQ,k,ro,cp,dt,cc,ccv,h,dx,nCells)
        timeSist = timeSist + get_wtime() - time0
c ...................................................................     

c ... Ax = B
c       write(*,*)'Ax=b :'
        time0 = get_wtime()
        call tdma_solver2(a(1,1),a(1,2),a(1,3),b,cellTemp
     .                   ,aux(1,1),aux(1,2),nCells)
        timeSolver = timeSolver + get_wtime() - time0
c ...................................................................
c
c ...
        call nodalInterpol(cells,cc,ccv,cellTemp,nodeTemp,nCells
     .                    ,nPoints)
c ...................................................................
c 
c ...
        call solExt(x,ye,t,dsqrt(k(1)/ro(1)*cp(1)),lComp,nPoints)
c ...................................................................
c
c ... 
c       write(*,*)'Write res :'
        time0 = get_wtime()
        call res(j,t,cellTemp,nCells ,nout1)
        call res(j,t,nodeTemp,nPoints,nout2)
c        call res(j,t,ye      ,nPoints,nout3)
c        call derr(ye,nodeTemp,nPoints)
        timeWres = timeWres + get_wtime() - time0
c ...................................................................
      enddo
c ...................................................................
c
c ...
      write(*,'(20a)')'done.'
c ...................................................................
c
c ...
      write(*,10)timeSist,timeSolver,timeWres
c ...................................................................
c
c ...
      deallocate(b,x,xc
     1          ,cellTemp,nodeTemp
     2          ,k       ,ro      ,cp
     3          ,a       ,aux
     4          ,cells   ,sQ      ,ye)
c ...................................................................
c
c ...
      close(nout1)
      close(nout2)
c      close(nout3)
c ......................................................................
      stop
   10 format(/,'Time Sist(s)   : ', f10.4,/
     1        ,'Time Solver(s) : ', f10.4,/
     2        ,'Time Wres(s)   : ', f10.4,/)
      end
c *********************************************************************
c
c *********************************************************************
c * DATA DE CRIACAO  : 11/09/2018                                     *
c * DATA DE MODIFICAO: 00/00/0000                                     *
c * ----------------------------------------------------------------- *
c * RES : escreve os resultados                                       *
c * ----------------------------------------------------------------- *
c * Parametros de entrada:                                            *
c * ----------------------------------------------------------------- *
c * step - passo de tempo                                             *
c * t    - tempo                                                      *
c * u    - vetor a ser escrito                                        *
c * n    - numero de pontos em u                                      *
c * nout - arquivo de saida                                           *
c * ----------------------------------------------------------------- *
c * Parametros de saida:                                              *
c * ----------------------------------------------------------------- *
c * ----------------------------------------------------------------- *
c * OBS:                                                              *
c * ----------------------------------------------------------------- *
c *********************************************************************
      subroutine res(step,t,u,n,nout)
      implicit none
      integer i,n,step,nout
c ...
      real(8) t,u(*)
c ...  coordenada do centroide    
      write(nout,'(i9,1x,f10.4)',advance='no')step,t
      do i = 1, n
        write(nout,'(1x,e22.15,1x)',advance='no')u(i)
      enddo
c .....................................................................      
      write(nout,*)
      return
      end
c .....................................................................
c *********************************************************************
c
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
c
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
