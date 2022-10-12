#include "farmingsimulator.h"

#include <iostream>

using namespace std;

int main()
{
    cout << "Roth SS2022" << endl;
    FarmingSimulator fm(3,3);//0,1,2
    fm.createOwner("MP");
    fm.createOwner("JB");
    fm.createOwner("FN");
    fm.createOwner("DM");
    fm.createOwner("SK");

    fm.addPlot(1,1, "MP", new Orchard(10));
    fm.addPlot(0,0, "JB", new Orchard(10));
    fm.addPlot(1,0, "FN", new Orchard(10));
    fm.addPlot(1,2, "DM", new Pasture(10));
    fm.addPlot(2,1, "SK", new Pasture(10));

    fm.report();

    //    Orchard* o1 = new Orchard(1,2,new Owner("MP"),10);
    //    Orchard* o2 = new Orchard(0,1,new Owner("JB"));
    //    Orchard* o3 = new Orchard(0,2,new Owner("FN"));
    //    Orchard* o4 = new Orchard(0,3,new Owner("DM"));

    //    Pasture* o5 = new Pasture(0,0,new Owner("MP"),10);
    //    Pasture* o6 = new Pasture(0,1,new Owner("JB"));
    //    Pasture* o7 = new Pasture(0,0,new Owner("FN"));
    //    Pasture* o8 = new Pasture(0,1,new Owner("SK"));

    //    addPlot(1,2,"MP", o1);
    //    addPlot(1,2,"MP", o5);
    //    addPlot(1,2,"MP", o3);
    //    addPlot(1,2,"MP", o4);
    //    addPlot(1,2,"MP", o5);
    //    addPlot(1,2,"MP", o6);
    //    addPlot(1,2,"MP", o7);
    //    addPlot(1,2,"MP", o8);

    /* a vicious circle
     * bool addPlot(int row, int col, const std::string& name, Plot* plot)
     * needs Plot as a parameter
     * but a plot itself also needs row, cl, name usw.
     * --> this should only be called internally
     *
     * ------> wrong because we have createOwner()
     */
    return 0;
}
