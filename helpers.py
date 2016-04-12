import math

def deltaPhi(phi1, phi2):
    PHI = abs(phi1 - phi2)
    if (PHI <= 3.14159265):
        return PHI
    else:
        return 2 * 3.14159265 - PHI
     
def deltaPhiWithSign(phi1, phi2):
    PI = 3.14159265
    if phi1 < 0 :  phi1 = phi1 + 2 * PI
    if phi2 < 0 :  phi2 = phi2 + 2 * PI
    deltaphi = phi1 - phi2
    if deltaphi > 2 * PI : deltaphi = deltaphi - 2 * PI
    if deltaphi < -2 * PI : deltaphi = deltaphi + 2 * PI
    if deltaphi > PI : deltaphi = -(2 * PI - deltaphi)
    if deltaphi < -PI: deltaphi = (2 * PI + deltaphi)
    return deltaphi;

def deltaR(eta1, phi1, eta2, phi2) :
    deta = eta1 - eta2
    dphi = deltaPhi(phi1, phi2)
    return math.sqrt(deta * deta + dphi * dphi)

def matchL3toL1(l3Tau, l1Taus, l1Jets):
    minDR = 100
    for l1Tau in l1Taus:
        dR = deltaR(l1Tau[1].eta(), l1Tau[1].phi(), l3Tau[1].eta(), l3Tau[1].phi())
        if dR < minDR: minDR = dR
    for l1Jet in l1Jets:
        dR = deltaR(l1Jet[1].eta(), l1Jet[1].phi(), l3Tau[1].eta(), l3Tau[1].phi())
        if dR < minDR: minDR = dR
    return minDR