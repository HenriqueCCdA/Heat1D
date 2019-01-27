"""
c *********************************************************************
c * DATA DE CRIACAO  : 07/11/2018                                     *
c * DATA DE MODIFICAO: 27/01/2019                                     *
c * ----------------------------------------------------------------- *
c * MONTASISTEMA : monta o sistema AX=B                               *
c * ----------------------------------------------------------------- *
c * Parametros de entrada:                                            *
c * ----------------------------------------------------------------- *
c * a      - matriz                                                   *
c *     a(:,0) - diagonal inferior                                    *
c *     a(:,1) - diagonal princial                                    *
c *     a(:,2) - diagonal princial                                    * 
c * b      - vetor de forças                                          *
c * temp   - temperatura do passo anterior                            *
c * sQ     - fonte de calor                                           *
c * k      - coeficiente de conducao termica                          *
c * ro     - massa especidica                                         *
c * cp     - calor espefifico                                         *
c * dt     - delta t                                                  *
c * cc[0]  - tipo de condicao de contorno                             *
c         1 - Temperatuta                                             *
c         2 - fluxo                                                   *
c         3 - resfriamento de newton                                  *
c * cc[1]  - valor numerico da condicao de contorno                   *
c * cc[2]  - valor de h                                               *
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
"""


def montaSistema(a, b, temp, sQ, k, ro, cp, dt , cc, dx , nCells):


    h = cc[0,2], cc[1,2]
    # ... temperatura pescrita
    aP0 = ro[0]*cp[0]*dx/dt
    kf  = (k[0] + k[1])*0.5e0
    aE  = kf/dx
    if cc[0][0] == 1:
        sP  = -2.0e0*k[0]/dx
        sU  = -sP*cc[0,1]
    # ... fluxo prescrito
    elif cc[0][0] == 2:
        sP  = 0.e0
        sU  = -cc[0][1]
    # ... lei de resfriamento
    elif cc[0][0] == 3:
        tmp = 1.e0 + (h[0]*2.e0*dx)/k[0]
        tmp = h[0]/tmp
        sP  = -tmp
        sU  = tmp*cc[0,1]
    # .................................................................
    # ... W
    a[0,0] = 0.e0
    # ... p
    a[0,1] = aP0 + aE - sP
    # ... E
    a[0,2] = -aE
    # ... b
    b[0] = sU + aP0*temp[0]
    # .................................................................

    # ... temperatura pescrita
    aP0 = ro[-1]*cp[-1]*dx/dt
    kf  = (k[-2] + k[-1])*0.5e0
    aW  = kf/dx
    if cc[1][0] == 1:
        sP  = -2.0e0*k[-1]/dx
        sU  = -sP*cc[1,1]
    # ... fluxo prescrito
    elif cc[1][0] == 2:
        sP  = 0.e0
        sU  = -cc[1,1]
    # ... lei de resfriamento
    elif cc[1][0] == 3:
        tmp = 1.e0 + (h[1]*2.e0*dx)/k[-1]
        tmp = h[1]/tmp
        sP  = -tmp
        sU  = tmp*cc[1,1]
    # .................................................................

    # ... W
    a[-1,0] = -aW
    # ... p
    a[-1,1] = aP0 + aW - sP
    # ... E
    a[-1,2] = 0.e0
    # ... b
    b[-1] = sU + aP0*temp[-1]
    # .................................................................

    # ...
    for i in range(1, nCells-1):
        aP0 = ro[i]*cp[i]*dx/dt
        # ... w
        kf = (k[i-1] + k[i])*0.5e0
        aW = kf/dx
        # ... w
        kf = (k[i] + k[i+1])*0.5e0
        aE = kf/dx
        # ...
        a[i,0] = -aW
        a[i,1] = aP0 + aW + aE
        a[i,2] = -aE
        # ...
        b[i] = aP0*temp[i]
    # .................................................................

    """
c *********************************************************************
c * DATA DE CRIACAO  : 27/01/2019                                     *
c * DATA DE MODIFICAO: 00/00/0000                                     *
c * ----------------------------------------------------------------- *
c * MONTASISTEMA_V2 : monta o sistema AX=B                            *
c * ----------------------------------------------------------------- *
c * Parametros de entrada:                                            *
c * ----------------------------------------------------------------- *
c * l      - diagonal inferior da matriz                              * 
c * d      - diagonal principal da matriz                             *
c * u      - diagonal supeior da matriz                               *
c * b      - vetor de forças                                          *
c * temp   - temperatura do passo anterior                            *
c * sQ     - fonte de calor                                           *
c * k      - coeficiente de conducao termica                          *
c * ro     - massa especidica                                         *
c * cp     - calor espefifico                                         *
c * dt     - delta t                                                  *
c * cc[0]  - tipo de condicao de contorno                             *
c         1 - Temperatuta                                             *
c         2 - fluxo                                                   *
c         3 - resfriamento de newton                                  *
c * cc[1]  - valor numerico da condicao de contorno                   *
c * cc[2]  - valor de h                                               *
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
"""


def montaSistema_v2(l ,d ,u, b, temp, sQ, k, ro, cp, dt , cc, dx , nCells):


    h = cc[0][2], cc[1][2]
    # ... temperatura pescrita
    aP0 = ro[0]*cp[0]*dx/dt
    kf  = (k[0] + k[1])*0.5e0
    aE  = kf/dx
    if cc[0][0] == 1:
        sP  = -2.0e0*k[0]/dx
        sU  = -sP*cc[0][1]
    # ... fluxo prescrito
    elif cc[0][0] == 2:
        sP  = 0.e0
        sU  = -cc[0][1]
    # ... lei de resfriamento
    elif cc[0][0] == 3:
        tmp = 1.e0 + (h[0]*2.e0*dx)/k[0]
        tmp = h[0]/tmp
        sP  = -tmp
        sU  = tmp*cc[0][1]
    # .................................................................
    # ... W
    l[0] = 0.e0
    # ... p
    d[0] = aP0 + aE - sP
    # ... E
    u[0] = -aE
    # ... b
    b[0] = sU + aP0*temp[0]
    # .................................................................

    # ... temperatura pescrita
    aP0 = ro[-1]*cp[-1]*dx/dt
    kf  = (k[-2] + k[-1])*0.5e0
    aW  = kf/dx
    if cc[1][0] == 1:
        sP  = -2.0e0*k[-1]/dx
        sU  = -sP*cc[1][1]
    # ... fluxo prescrito
    elif cc[1][0] == 2:
        sP  = 0.e0
        sU  = -cc[1][1]
    # ... lei de resfriamento
    elif cc[1][0] == 3:
        tmp = 1.e0 + (h[1]*2.e0*dx)/k[-1]
        tmp = h[1]/tmp
        sP  = -tmp
        sU  = tmp*cc[1][1]
    # .................................................................

    # ... W
    l[-1] = -aW
    # ... p
    d[-1] = aP0 + aW - sP
    # ... E
    u[-1] = 0.e0
    # ... b
    b[-1] = sU + aP0*temp[-1]
    # .................................................................

    # ...
    for i in range(1, nCells-1):
        aP0 = ro[i]*cp[i]*dx/dt
        # ... w
        kf = (k[i-1] + k[i])*0.5e0
        aW = kf/dx
        # ... w
        kf = (k[i] + k[i+1])*0.5e0
        aE = kf/dx
        # ...
        l[i] = -aW
        d[i] = aP0 + aW + aE
        u[i] = -aE
        # ...
        b[i] = aP0*temp[i]
    # .................................................................
