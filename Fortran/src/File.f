c *********************************************************************
c * DATA DE CRIACAO  : 11/09/2018                                     *
c * DATA DE MODIFICAO: 16/09/2018                                     *
c * ----------------------------------------------------------------- *
c * REAFILE : leitura dos arquivos de dados                           *
c * ----------------------------------------------------------------- *
c * Parametros de entrada:                                            *
c * ----------------------------------------------------------------- *
c * lComp   - nao definido                                            *
c * nDiv    - nao definido                                            *
c * dt      - nao definido                                            *
c * nStep   - nao definido                                            *
c * cc      - nao definido                                            *
c * ccv     - nao definido                                            *
c * temp0   - nao definido                                            *
c * nameOut - nao definido                                            *
c * ----------------------------------------------------------------- *
c * Parametros de saida:                                              *
c * ----------------------------------------------------------------- *
c * lComp   - comprimento da barra                                    *
c * nDiv    - numero de divisoes                                      *
c * dt      - delta                                                   *
c * nStep   - numero de passo de tempo                                *
c * cc      - tipo de condicao de contorno                            *
c *       1 - Temperatuta                                             *
c *       2 - fluxo                                                   *
c *       3 - lei de resfriamento de newton                           *
c * ccv     - calor da condicao de contorno                           *
c * temp0   - temperatura inicial                                     *
c * prop    - proriedades do material                                 *
c *         1 - condutividade termica                                 *
c *         2 - massa especifica                                      *
c *         3 - calor especifico                                      *
c * nameOut - nome do arquivo de saida                                *
c * ----------------------------------------------------------------- *
c * OBS:                                                              *
c * ----------------------------------------------------------------- *
c *********************************************************************
      subroutine readfile(lComp,nDiv,dt,nStep,cc,ccv,h,temp0,prop
     .                   ,nameOut,nin)
      implicit none
      include 'string.fi'
      logical flag
      character(len=80) nameOut, dum
      character(len=15) rc,macro(36),string
      integer nDiv,nStep,cc(2),nin,j,nmc,ier,maxLine
      real(8) dt,ccv(2),lComp,temp0,h(2),prop(3)
c ......................................................................
      data macro/'end            ','output         ','lenth          ',
     1           'ndiv           ','dt             ','nstep          ',
     2           'cce            ','ccd            ','initialt       ',
     3           'prop           ','               ','               ',
     4           '               ','               ','               ',
     5           '               ','               ','               ',
     6           '               ','               ','               ',
     7           '               ','               ','               ',
     8           '               ','               ','               ',
     9           '               ','               ','               ',
     1           '               ','               ','               ',
     2           '               ','               ','               '/
      data nmc /36/      
c ......................................................................
c
c ...
      h(1) = 0.0d0
      h(2) = 0.0d0  
c ...
      open(unit=nin,file='input.dat')
c ... 
      maxLine = 0
      flag = .true.
      do while(flag)
        maxLine = maxLine + 1
        call readmacro(nin,.true.,ier)
        write(rc,'(15a)') (word(j),j=1,15)
c .......................................................................
c
c ...
        if(rc .eq. macro(1) ) then
          flag = .false.
c .......................................................................
c
c ...
        else if(rc .eq. macro(2) ) then
          call readmacro(nin,.false.,ier)
          write(nameOut,'(80a)') (word(j),j=1,80) 
c .......................................................................
c
c ...
        else if(rc .eq. macro(3)) then
          call readmacro(nin,.false.,ier)
          write(string,'(15a)') (word(j),j=1,15) 
          read(string, *, err=200,end = 200) lComp
c .......................................................................
c
c ...
        else if(rc .eq. macro(4)) then
          call readmacro(nin,.false.,ier)
          write(string,'(15a)') (word(j),j=1,15) 
          read(string, *, err=200,end = 200) nDiv
c .......................................................................
c
c ...
        else if(rc .eq. macro(5)) then
          call readmacro(nin,.false.,ier)
          write(string,'(15a)') (word(j),j=1,15) 
          read(string, *, err=200,end = 200) dt
c .......................................................................
c
c ...
        else if(rc .eq. macro(6)) then
          call readmacro(nin,.false.,ier)
          write(string,'(15a)') (word(j),j=1,15) 
          read(string, *, err=200,end = 200) nStep
c .......................................................................
c
c ...
        else if(rc .eq. macro(7)) then
          call readmacro(nin,.false.,ier)
          write(string,'(15a)') (word(j),j=1,15) 
          read(string, *, err=200,end = 200) cc(1)
c ...
          if(cc(1) .eq. 3) then
c ...
            call readmacro(nin,.false.,ier)
            write(string,'(15a)') (word(j),j=1,15) 
            read(string, *, err=200,end = 200) ccv(1)
c ...
            call readmacro(nin,.false.,ier)
            write(string,'(15a)') (word(j),j=1,15) 
            read(string, *, err=200,end = 200) h(1)
c ......................................................................
          else
c ...
            call readmacro(nin,.false.,ier)
            write(string,'(15a)') (word(j),j=1,15) 
            read(string, *, err=200,end = 200) ccv(1)
c ......................................................................
          endif
c ......................................................................
c
c ...
        else if(rc .eq. macro(8)) then
          call readmacro(nin,.false.,ier)
          write(string,'(15a)') (word(j),j=1,15) 
          read(string, *, err=200,end = 200) cc(2)
c ...
          if(cc(2) .eq. 3) then
c ...
            call readmacro(nin,.false.,ier)
            write(string,'(15a)') (word(j),j=1,15) 
            read(string, *, err=200,end = 200) ccv(2)
c ...
            call readmacro(nin,.false.,ier)
            write(string,'(15a)') (word(j),j=1,15) 
            read(string, *, err=200,end = 200) h(2)
c ......................................................................
          else
c ...
            call readmacro(nin,.false.,ier)
            write(string,'(15a)') (word(j),j=1,15) 
            read(string, *, err=200,end = 200) ccv(2)
c ......................................................................
          endif
c .......................................................................
c
c ...
        else if(rc .eq. macro(9)) then
          call readmacro(nin,.false.,ier)
          write(string,'(15a)') (word(j),j=1,15) 
          read(string, *, err=200,end = 200) temp0   
c .......................................................................
c
c .......................................................................
c
c ...
        else if(rc .eq. macro(10)) then
c ... k
          call readmacro(nin,.false.,ier)
          write(string,'(15a)') (word(j),j=1,15) 
          read(string, *, err=200,end = 200) prop(1)  
c ... ro
          call readmacro(nin,.false.,ier)
          write(string,'(15a)') (word(j),j=1,15) 
          read(string, *, err=200,end = 200) prop(2)  
c ... cp
          call readmacro(nin,.false.,ier)
          write(string,'(15a)') (word(j),j=1,15) 
          read(string, *, err=200,end = 200) prop(3)  
c .......................................................................
c
c ...
        else if(maxLine .ge. 100) then
          print*,'*** Numero de linhas maxima no arquivo de entrada ' 
     1          ,'excedido!!'
          stop  
        endif
c .......................................................................
c
c ...
      enddo
c ...
      close(nin)
c ...
      write(*,'(a)')'***********************************************'
      write(*,'(a,f16.6)')'lComp :',lComp
      write(*,'(a,i16)')'nDiv  :',nDiv
      write(*,'(a,f16.6)')'dt    :',dt
      write(*,'(a,f16.6)')'dx    :',lComp/nDiv
      write(*,'(a,i16)')  'step  :',nStep
      write(*,'(a,i4,1x,f16.6,1x,f16.6)')'cce   :',cc(1),ccv(1),h(1)
      write(*,'(a,i4,1x,f16.6,1x,f16.6)')'ccd   :',cc(2),ccv(2),h(2)
      write(*,'(a,f16.6)')'Temp0 :',temp0
      write(*,'(a,f16.6)')'k     :',prop(1)
      write(*,'(a,f16.6)')'ro    :',prop(2)
      write(*,'(a,f16.6)')'cp    :',prop(3)
      write(*,'(a)')'***********************************************'
c .....................................................................
c
c ...
      return
c .....................................................................
c
c ...
  200 continue
      print*,'*** Erro na leitura da arquivo de entrada !'
      call help()
      stop  
c .....................................................................
c
c ...         
      end
c **********************************************************************
c
c *********************************************************************
c * DATA DE CRIACAO  : 16/09/2018                                     *
c * DATA DE MODIFICAO: 00/00/0000                                     *
c * ----------------------------------------------------------------- *
c * HELP : Exemplo de arquivos de entrada                             *
c * ----------------------------------------------------------------- *
c * Parametros de entrada:                                            *
c * ----------------------------------------------------------------- *
c * ----------------------------------------------------------------- *
c * Parametros de saida:                                              *
c * ----------------------------------------------------------------- *
c * ----------------------------------------------------------------- *
c * OBS:                                                              *
c * ----------------------------------------------------------------- *
c *********************************************************************
      subroutine help()
      implicit none
      character(len=15) macro(36)
      integer i
c ......................................................................
      data macro/'end            ','output file.out','lenth 0.02     ',
     1           'ndiv 10        ','dt 0.2         ','nstep 200      ',
     2           'cce 1 -10.0    ','ccd 3 -10.0 2.0','initialt 10.0  ',
     3           '               ','               ','               ',
     4           '               ','               ','               ',
     5           '               ','               ','               ',
     6           '               ','               ','               ',
     7           '               ','               ','               ',
     8           '               ','               ','               ',
     9           '               ','               ','               ',
     1           '               ','               ','               ',
     2           '               ','               ','               '/
c ...
      print*,'Exemplo de arquivo de dados:'
      do i = 2, 9
        print*,macro(i)
      enddo
      print*,'end'
c ...
      return
      end
c **********************************************************************
c
c **********************************************************************
      subroutine readmacro(nin,newline,ier)
c **********************************************************************
c *                                                                    *
c *   Subroutine READMACRO: le uma macro numa linha nova ou a partir   *
c *                         da coluna line_col de uma linha lida       *
c *                         anteriormente e armazenada em line(*)      *
c *                                                                    *
c *   Parametros de entrada:                                           *
c *                                                                    *
c *   nin - numero do arquivo de entrada                               *
c *   newline = .true.  - nova linha deve ser lida                     *
c *           = .false. - macro deve ser lida a partir da coluna       *
c *                       line_col em line(*)                          *
c *   ier     = codigo de erro    (  0 - sem erro                      *
c *                                  1 - com erro)                     *
c **********************************************************************
      implicit none
      include 'string.fi'
      integer j,k,ier,nin
      logical newline
c ......................................................................
      if(newline) then
         line_col = 1
         read(nin,'(500a1)',err = 200,end = 200) (line(j),j=1,maxstrl)
      endif
c ......................................................................
      do j = 1, maxstrl
         word(j) = ' '
      enddo
      strl = 0
      if(line_col .gt. maxstrl) return
c ......................................................................
      do while (line(line_col) .eq. ' ')
         line_col = line_col + 1
         if (line_col .gt. maxstrl) return         
      end do
c ......................................................................
      do while ( (line(line_col) .ne. ' ') .and.
     .           (line(line_col) .ne. CHAR(13)) )
         strl = strl + 1
         line_col = line_col + 1
         if (line_col .gt. maxstrl) goto 100
      end do
c ......................................................................
  100 continue      
      k = line_col-strl
      do j = 1, strl
         write(word(j),'(a)') line(k)
         k = k + 1
      end do 
      ier = 0     
      return
c ......................................................................
  200 continue
      ier = 1
      return
c ......................................................................
      end 
c ======================================================================