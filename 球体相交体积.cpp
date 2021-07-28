void solve(double x1,double y1,double z1,double r1,double x2,double y2,double z2,double r2){
    double ans=0;
    //球心距离
    double dis=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2));
    //相离或相切
    if(dis>=r1+r2){
        ans=0;
    }
    //内含或内切
    else if (dis+r1<=r2){
        ans=(4.00/3.00)*pi*r1*r1*r1;
    }
    else if(dis+r2<=r1){
        ans=(4.00/3.00)*pi*r2*r2*r2;
    }
    //相交
    else{
        //计算cos1
        double cal=(r1*r1+dis*dis-r2*r2)/(2.00*dis*r1);
        //计算h1
        double h=r1*(1-cal);
        //计算球缺1体积
        ans+=(1.00/3.00)*pi*(3.00*r1-h)*h*h;
        //计算cos2
        cal=(r2*r2+dis*dis-r1*r1)/(2.00*dis*r2);
        //计算h2
        h=r2*(1.00-cal);
        //计算球缺2体积
        ans+=(1.00/3.00)*pi*(3.00*r2-h)*h*h;
    }
    printf("%.3f\n",ans);
}
