import Tridiagonal as tr
import ReadFile as rf
import Sistema as si
import Grid as gr
import time as tm


def main():

    filesInf = rf.readFile(fileName="../input/newton.dat")

    # ...
    nCells = filesInf['ndiv']
    nPoints = filesInf['ndiv'] + 1
    length = filesInf['length']
    preName = filesInf['output']
    nStep = filesInf['nstep']
    # ......................................................................

    # ... gera o grid
    x, xc, cells, dx = gr.grid(length, nPoints, nCells)
    # ......................................................................

    # ...
    timeSist = timeWres = timeSolver = 0.e0

    # ...
    t = 0.0
    dt = filesInf['dt']
    k = nCells * [filesInf['prop'][0]]
    ro = nCells * [filesInf['prop'][1]]
    cp = nCells * [filesInf['prop'][2]]
    cc = [filesInf['cce'], filesInf['ccd']]
    sQ = nCells * [0.0]
    a = [[0.0, 0.0, 0.0] for x in range(nCells)]
    b = nCells * [0.0]
    nodeTemp = nPoints * [0.0]
    cellTemp = nCells * [filesInf['initialt']]
    # .................................................................

    # ...
    fileResCell = open(preName +'_cell.python', 'w')
    fileResNode = open(preName +'_node.python', 'w')
    # .................................................................

    # ...
    gr.nodalInterpol(cells, cc, cellTemp, nodeTemp, nCells, nPoints)
    # ................................1.................................

    # ...
    time0 = tm.time()
    gr.res(0, 0.0, xc,  nCells, fileResCell)
    gr.res(0, 0.0,  x, nPoints, fileResNode)
    timeWres += tm.time() - time0
    # .................................................................

    # ... temperatura inicial
    time0 = tm.time()
    gr.res(0, 0.0, cellTemp, nCells, fileResCell)
    gr.res(0, 0.0, nodeTemp, nPoints, fileResNode)
    timeWres += tm.time() - time0
    # .................................................................

    # ...
    print("Running ...")
    for j in range(1,nStep+1):

        # ...
#        print("Step : {0}\nTime(s) : {1}".format(j, t))
        t += dt
        # .............................................................

        # ... monta sistema
        time0 = tm.time()
        si.montaSistema(a, b,  cellTemp, sQ, k, ro, cp, dt , cc,\
                        dx, nCells)
        timeSist += tm.time() - time0
        # .............................................................

        # ... Ax = B
        time0 = tm.time()
        tr.tdma_solver1(a, b, cellTemp, nCells)
        timeSolver += tm.time() - time0
        # .............................................................

        # ...
        gr.nodalInterpol(cells, cc, cellTemp, nodeTemp, nCells, nPoints)
        # ................................1.................................

        # ... temperatura inicial
        time0 = tm.time()
        gr.res(j, t, cellTemp, nCells, fileResCell)
        gr.res(j, t, nodeTemp, nPoints, fileResNode)
        timeWres += tm.time() - time0
        # .................................................................

    # .................................................................

    # ...
    print("done.")
    # .................................................................

    # ...
    print("Time Sist(s)   : {0:.4f}\n"\
          "Time Solver(s) : {1:.4f}\n"\
          "Time Wres(s)   : {2:.4f}".format(timeSist, timeSolver, timeWres))
    # .................................................................


    # ...
    fileResCell.close()
    fileResNode.close()
# ......................................................................


if __name__ == '__main__':
    main()
