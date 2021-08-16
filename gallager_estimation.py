import math
import sys
from scipy.special import erfc

def get_thr(k, q, iter, c = 1):

    thr_res = [ 0 for i in range(iter) ]
    var_res = [ 0.0 for i in range(iter) ]

    q118 = int(round(q / 18, 0))
    k23 = 2 * k / 3

    pi_prv = 1 / 3
    var_prv = 8 * k / 9
    for i in range(iter):
        if var_prv == 0:
            break
        pi_best = 0
        var_best = float("inf")
        aux = (math.sqrt(2 * var_prv))
        for t in range(q118 + 1):
            pi_p = erfc((q118 + t) / aux)
            pi_m = erfc((q118 - t) / aux)
            pi = (pi_prv * (1 - pi_p)) + ((1 - pi_prv) * (1 - pi_m))
            if (i == 0):
                var = 8 / 9 * k23 * (pi_m + (2 * pi_p))
            else:
                var = c * k23 * ((pi_prv * pi_p) + ((1 - pi_prv) * (pi_m + (1.5 * pi_p))))
            if var < var_best:
                pi_best = pi
                var_best = var
                thr_res[i] = t
                var_res[i] = var
        pi_prv = pi_best
        var_prv = var_best

    return thr_res, var_res

def main():

    argc = len(sys.argv)

    if argc < 4:
        print("Usage: ", sys.argv[0], "k q iter [c_ini [c_max c_stp]]\n")
        return

    k = int(sys.argv[1])
    q = int(sys.argv[2])
    iter = int(sys.argv[3])

    if argc == 4:
        c_ini = 1.0
        c_max = 1.0
        c_stp = 1.0
    elif argc < 7:
        c_ini = float(sys.argv[4])
        c_max = c_ini
        c_stp = 1.0
    else:
        c_ini = float(sys.argv[4])
        c_max = float(sys.argv[5])
        c_stp = float(sys.argv[6])

    c = c_ini
    thr_prv = []
    for i in range(math.floor((c_max - c_ini) / c_stp) + 1):
        thr, var = get_thr(k, q, iter, c)
        if (thr != thr_prv):
            print("c = {0:1.6}".format(c))
            print("thr_i = {0}".format(thr))
            print("var_i = {0}\n".format(var))
            thr_prv = thr
        c = c + c_stp

if __name__ == '__main__':
    main()
