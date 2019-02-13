#include "udetection.h"
#define THRESH 50
#define DELTA 35
#define DELTA_EDGE 10
#define DISTANCE 300
#define RECT_DELTA 30//10
#define MIN_LINE_SIZE 80
#define BODY_AREA 1000
#define BODY_AREA2 1000
#define LINE_THICKNESS 6
#define CIRCLE_THICKNESS 1
#define GATE_DISTANCE 40
Scalar color;
RNG rng(12345);
Mat frame;
Mat rgb;
int i=0;
double Max_Gate_Area =DBL_MIN;
struct myclassX {
    bool operator() (Point pt1, Point pt2) { return (pt1.x < pt2.x);}
} myobject;

struct myclassY {
    bool operator() (Point pt1, Point pt2) { return (pt1.y < pt2.y);}
} myobject1;


UDetection::UDetection()
{
    croped =false;
    up_down = 0;
}
vector<Point> UDetection::getRed_contour() const
{
    return red_contour;
}

void UDetection::setColor_tag(const ColorDetection::Colors &value)
{
    color_tag = value;
}
void UDetection::setCroped(bool value)
{
    croped = value;
}
void UDetection::setUp_down(int value)
{
    up_down = value;
}





vector<Point> UDetection::getYellow_contour() const
{
    return yellow_contour;
}


vector<Vec4i> UDetection::detectLines(Mat src)
{

    Mat canny;
    vector<vector<Point> > contours;

    frame=src.clone();
    //vector<Point> approx;

    vector<Vec4i> lines;

    vector<Vec4i> lines_prim;

    //put them in a method

    //medianBlur(frame,frame,3);
    // GaussianBlur(frame,frame,Size(3,3),-3);
    Canny(frame,canny,0,50,5);//50,200,3
    // imshow("CAnny 0",canny);

    HoughLinesP(canny, lines, 8 , CV_PI/180,80, 50, 100  );//50,50,10  //threshold =180
    cvtColor(frame,frame,CV_GRAY2BGR);
    qDebug()<<"HOUGH LINE SIZE :"<<lines.size();
    //hasIntersection(lines,frame);
    for( size_t i = 0; i < lines.size(); i++ )
    {
        Vec4i l = lines[i];

        color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
        double line_size=sqrt(abs((l[0]-l[2])*(l[0]-l[2])+( l[1]-l[3] )*( l[1]-l[3] )));

        if(line_size > MIN_LINE_SIZE){
            //            if(isSlopeEqual(l,l1) && isHorizental(l))
            line(frame, Point(l[0], l[1]), Point(l[2], l[3]), color, 3, CV_AA);
            //qDebug()<<"TRUE : line size is : "<<line_size;
            lines_prim.push_back(l);


        }
        else;
        // qDebug()<<"FAKE : line size is : "<<line_size;

    }
    //namedWindow("RAW LINES",CV_WINDOW_NORMAL);
    imshow("RAW LINES",frame);
    qDebug()<<"*** LINE SIZE : "<<lines_prim.size()<<"***";
    return lines_prim;

}

bool UDetection::detectU_shapes(Mat src)
{

    Mat frame=src.clone();

    rgb=frame.clone();

    int a=clock();

    cvtColor(rgb,rgb,CV_GRAY2BGR);

    int b=clock();
    //vector<Vec4i> lines=detectLines(src);

    color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );


    bool notClose = true;//!isClose4Vertex(lines);

    int counter=0;
    if(detecGate(src)){

        imshow("Detected Lines",rgb);
        return true;
    }

    return false;

}

bool UDetection::is_90Deg(Vec4i l1, Vec4i l2)
{

    if((isHorizental(l1) & isVertical(l2))
            || (isHorizental(l2) & isVertical(l1)))
        return true;
    else
        return false;
}


double UDetection::angle(Point pt1, Point pt2)
{


    double angle = atan2(pt1.y - pt2.y, pt1.x - pt2.x);
    return angle * 180 / CV_PI;

}

bool UDetection::isSlopeEqual(Vec4i l1, Vec4i l2)
{

    double m1=0;
    double m2=0;


    Point start_pt1= Point(l1[0], l1[1]);
    Point end_pt1  = Point(l1[2], l1[3]);

    int delta_x1=start_pt1.x - end_pt1.x;
    if(delta_x1 !=0)
        m1 = abs((start_pt1.y - end_pt1.y)/(delta_x1));

    Point start_pt2= Point(l2[0], l2[1]);
    Point end_pt2  = Point(l2[2], l2[3]);

    int delta_x2=start_pt2.x - end_pt2.x;

    if(delta_x2 !=0)
        m2 = abs((start_pt2.y - end_pt2.y)/(delta_x2));

    if(delta_x2 ==0 && delta_x1==0)
        return true;

    return abs(m1-m2)<7;
}

bool UDetection::isSlopeEqual(Point start_pt1, Point end_pt1, Point start_pt2, Point end_pt2, Point start_pt3, Point end_pt3)
{

    double m1=0;
    double m2=0;
    double m3=0;

    int delta_x1=start_pt1.x - end_pt1.x;
    if(delta_x1 !=0)
        m1 = abs((start_pt1.y - end_pt1.y)/(delta_x1));

    int delta_x2=start_pt2.x - end_pt2.x;

    if(delta_x2 !=0)
        m2 = abs((start_pt2.y - end_pt2.y)/(delta_x2));

    int delta_x3=start_pt3.x - end_pt3.x;

    if(delta_x3 !=0)
        m3 = abs((start_pt3.y - end_pt3.y)/(delta_x3));


    if(delta_x3 ==0 && delta_x2 ==0 && delta_x1==0)
        return true;

    qDebug()<<"m1 : "<<m1<<" m2 : "<<m2<<" m3 : "<<m3;
    return abs(m1-m2)<3 && abs(m3-m2)<3;
}

bool UDetection::isHorizental(Vec4i l)
{

    if(abs(l[1]-l[3])< 10)
        return true;
    else return false;
}

bool UDetection::isClose4Vertex(vector<Vec4i> lines)
{

    Point maxP1;
    int maxY=0,minX=1000,maxX=0;
    int tempMax,tempMin;
    for(int i=0;i<lines.size();i++){
        if(isHorizental(lines[i])){
            maxY=lines[i][1];//ys are the same
            tempMax=lines[i][2];
            tempMin=lines[i][0];
            /*if(lines[i][3]>lines[i][1])
                tempMax=lines[i][3];
            if(tempMax >maxY)
                maxY=tempMax;*/
            if(lines[i][0]>lines[i][2]){
                tempMax=lines[i][0];
                tempMin=lines[i][2];
                if(tempMax >maxX)
                    maxX=tempMax;
                if(tempMin <minX)
                    minX=tempMin;
            }
        }
    }
    int startX,endX;
    for(int k=0;k<lines.size();k++){
        //startY = lines[k][1];
        //endY = lines[k][3];
        startX= lines[k][1];
        endX = lines[k][3];
        if(startX > endX){

            endX =lines[k][1];
            startX = lines[k][3];
        }
        if(isHorizental(lines[k]))
            //if(abs(startY - maxY) < RECT_DELTA &&
            //       abs(endY - maxY) < RECT_DELTA )

            if(abs(startX - minX) < RECT_DELTA &&
                    abs(endX - maxX) < RECT_DELTA )
            {
                line(rgb,Point(lines[k][0],lines[k][1]),Point(lines[k][2],lines[k][3]),Scalar(255,0,0),10);


                circle(rgb,Point(lines[k][0],lines[k][1]),10,Scalar(0,255,255),5);
                circle(rgb,Point(lines[k][2],lines[k][3]),10,Scalar(0,255,255),5);


                qDebug("IS LKE A RECTTTTTT");
                return true;
            }

    }

    return false;



}

bool UDetection::isVertical(Vec4i l)
{

    if(abs(l[0]-l[2])< 10)
        return true;
    else
        return false;
}

bool UDetection::hasIntersectionPoints(Point p1, Point p2)
{
    if(abs(p1.x-p2.x)<DELTA && abs(p1.y-p2.y)<DELTA){

        // qDebug()<<"DELTA X : "<<abs(p1.x-p2.x);
        //qDebug()<<"DELTA Y : "<<abs(p1.y-p2.y);
        return true;
    }
    return false;
}

bool UDetection::hasIntersectionWithOthers(Point p, vector<Vec4i> lines, int index1, int index2)
{
    bool found=false;
    int distance = findMaxLength(lines);
    qDebug()<<"MAX DISTANCE : "<<distance;
    for(int k=0;k<lines.size() ; k++){
        if(k!=index1 & k!=index2)
            if( isVertical(lines[k]))
            {

                //                qDebug()<<"DISTANCE 1 = "<<abs(lines[k][0]-lines[index2][0]);
                //                qDebug()<<"DISTANCE 2 = "<<abs(lines[k][0]-lines[index1][0]);
                if ( !isSlopeEqual(lines[index1],lines[k]) //XOR (not equal both)
                     & isSlopeEqual(lines[index2],lines[k])
                     & abs(lines[k][0]-lines[index2][0]) > distance - 60){


                    qDebug()<<"DISTANCE 1 = "<<abs(lines[k][0]-lines[index2][0]);
                    circle(rgb,Point((lines[k][2]+lines[index2][2])/2,(lines[k][3]+lines[k][1])/2),10,Scalar(0,255,255),5);
                    found =true;
                }
                else if  ( isSlopeEqual(lines[index1],lines[k]) //XOR (not equal both)
                           & !isSlopeEqual(lines[index2],lines[k])
                           & abs(lines[k][0]-lines[index1][0]) > distance - 60) {
                    qDebug()<<"DISTANCE 2 = "<<abs(lines[k][0]-lines[index1][0]);
                    circle(rgb,Point((lines[k][2]+lines[index1][2])/2,(lines[k][3]+lines[k][1])/2),10,Scalar(0,255,255),5);
                    found =true;
                }

            }

        if(found){
            //if delta  x!=0 then ot in the same line
            if(hasIntersectionPoints(p,Point(lines[k][0],lines[k][1]))) {



                circle(rgb,Point(lines[k][2],lines[k][3]),10,Scalar(0,0,255),5);
                circle(rgb,p,10,Scalar(0,0,255),5);

                line(rgb,p,Point(lines[k][2],lines[k][3]),color,LINE_THICKNESS);


                qDebug("HAS INTERSECTION WITH OTHERS");
                return true;
            }
            else if( hasIntersectionPoints(p,Point(lines[k][2],lines[k][3]))){

                circle(rgb,Point(lines[k][0],lines[k][1]),10,Scalar(0,0,255),5);
                circle(rgb,p,10,Scalar(0,0,255),5);

                line(rgb,p,Point(lines[k][0],lines[k][1]),color,LINE_THICKNESS);


                qDebug("HAS INTERSECTION WITH OTHERS");
                return true;
            }
        }
    }


    return false;
}

bool UDetection::detectBoundedRects(Mat src)
{
    qDebug()<<"IN BOUNDING RECT DETECTION";
    Mat input =src.clone(),output;
    Mat threshold_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    bool found=false;

    /// Detect edges using Threshold
    threshold( input, threshold_output, 100, 255, THRESH_BINARY );
    /// Find contours
    findContours( threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

    /// Approximate contours to polygons + get bounding rects and circles
    vector<vector<Point> > contours_poly( contours.size() );
    vector<Rect> boundRect( contours.size() );
    Scalar color;

    cvtColor(threshold_output,output,CV_GRAY2BGR);
    for( int i = 0; i < contours.size(); i++ )
    {

        approxPolyDP( Mat(contours[i]), contours_poly[i], 8, true );

        drawContours(output,contours,i,color,3);
        //boundRect[i] = boundingRect( Mat(contours_poly[i]) );
        color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );

        drawContours(output,contours,i,color,5);

        qDebug()<<"CONTOUR SIZE : "<<contours_poly[i].size();

        qDebug()<<"CONTOUR AREA : "<<contourArea(contours[i]);

        if( contours_poly[i].size()==8 /*&&
                                                                                                                                            isContourConvex(contours_poly[i])*/){
            if(contourArea(contours[i]) > BODY_AREA){


                qDebug("8 VERTEX ");


                if(isU(contours_poly[i])){

                    found =true;
                    break;
                }
            }


        }
    }

    imshow("Bounding Rect ",output);
    if(found)
        return true;  ///return after fist one found

    return false;

}

bool UDetection::detectUBySecondForm(vector<Point> points)
{
    //if 2 top edges of gate and 1 bottom are equal = gate detected

    sort(points.begin(),points.end(),myobject1);
    Point p1=points[0];

    Point p2=points[1];

    Point p3=points[2];

    Point p4=points[3];

    Point p5=points[points.size()-2];

    Point p6=points[points.size()-1];

    //  qDebug()<<"SORTED POLY POINTS Y: "<<p1.y <<"    "<<p2.y <<"    "<<p3.y <<"    "<<p4.y ;

    //distance between top and down more than X cm

    qDebug()<<"distance = "<<p6.y - p1.y;
    if((p6.y - p1.y )> (croped ? GATE_DISTANCE/2 :GATE_DISTANCE) &&
            isSlopeEqual(p1,p3,p2,p4,p5,p6))
        return true;
    return false;


}

bool UDetection::isInsideEmpty(Mat src)
{

}
bool UDetection::compareContourAreas ( std::vector<cv::Point> contour1, std::vector<cv::Point> contour2 ) {
    double i = fabs( contourArea(cv::Mat(contour1)) );
    double j = fabs( contourArea(cv::Mat(contour2)) );
    return ( i > j );
}

bool UDetection::detecGate(Mat src)
{
    qDebug()<<"IN GATE DETECTION";
    Mat input =src.clone(),output;
    Mat threshold_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    bool foundU=false;
    bool foundEdge=false;


    int x_edge_counter=0,y_edge_counter=0;

    /// Detect edges using Threshold
    threshold( input, threshold_output, 100, 255, THRESH_BINARY );
    /// Find contours

    findContours( threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

    /// Approximate contours to polygons + get bounding rects and circles
    vector<vector<Point> > contours_poly( contours.size() );
    Scalar color;

    // sort contours descending
    sort(contours.begin(),contours.end(),compareContourAreas);
    cvtColor(threshold_output,output,CV_GRAY2BGR);

    int a=clock();
    for( int i = 0; i < contours.size(); i++ )
    {

        qDebug()<<"contour area : "<<contourArea(contours[i]);
        if(contourArea(contours[i]) > (croped ? BODY_AREA/2 :BODY_AREA) ){

            approxPolyDP( Mat(contours[i]), contours_poly[i], 8, true );

            //boundRect[i] = boundingRect( Mat(contours_poly[i]) );
            color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );

            drawContours(output,contours,i,color,5);


            approxPolyDP( Mat(contours[i]), contours_poly[i], 8, true );

            // drawContours(output,contours,i,color,3);
            color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );

            int poly_size= contours_poly[i].size();

            qDebug()<<"CONTOUR SIZE"<<poly_size;
            qDebug()<<"contour area : "<<contourArea(contours[i]);

            for(int l=0;l<poly_size ;l++)

                circle(output,contours_poly[i][l],10,Scalar(45,145,45),10);

            //whole gate check
            Point p=findCenterPoint(contours_poly[i]);
            circle(output,p,10,Scalar(45,145,45),20);
            imshow("Bounding Rect ",output);
            if( poly_size==8 ){

                for(int l=0; l<contours_poly[i].size();l++)
                {
                    circle(output,contours_poly[i][l],10,Scalar(255,0,0),20);
                }
                qDebug("8 VERTEX ");

                if(isU(contours_poly[i])){

                    foundU =true;

                    qDebug("U DETECTION FIRST ALGO");
                    imshow("Bounding Rect ",output);
                    if(color_tag==ColorDetection::RED)
                        red_contour =contours[i];
                    else

                        if(color_tag==ColorDetection::YELLOW)
                            yellow_contour =contours[i];
                    return true;  ///return after fist one found


                }
                else if(detectUBySecondForm(contours_poly[i])){

                    foundU =true;

                    qDebug("U DETECTION SECOND ALGO");
                    imshow("Bounding Rect ",output);
                    if(color_tag==ColorDetection::RED)
                        red_contour =contours[i];
                    else

                        if(color_tag==ColorDetection::YELLOW)
                            yellow_contour =contours[i];

                    return true;  ///return after fist one found
                }
            }
            if( poly_size == 6 || poly_size == 7 || poly_size==9 || poly_size==10){ //in real gate put 10 instead of 11

                if(detectUBySecondForm(contours_poly[i])){

                    foundU =true;

                    qDebug("U detection SECOND ALGO");
                    imshow("Bounding Rect ",output);
                    if(color_tag==ColorDetection::RED)
                        red_contour =contours[i];
                    else

                        if(color_tag==ColorDetection::YELLOW)
                            yellow_contour =contours[i];

                    return true;  ///return after fist one found
                }
            }

            // edges check
            if(contourArea(contours[i]) > (croped ? BODY_AREA2/2 :BODY_AREA2)
                    && (poly_size ==4 || poly_size == 6)){

                qDebug()<<"IN EDGE DETECTION ";

                qDebug()<<"updown "<<up_down;
                int MAX_Y=240;
                int MIN_Y=0;
                if(croped)
                        MAX_Y=120;


                qDebug()<<"min y = "<<MIN_Y;
                for(int l=0; l < poly_size ; l++){
                    Point p=contours_poly[i][l];
                    circle(output,p,10,Scalar(255,0,0),5);
                    //qDebug()<<" EDGE : P.X = "<<p.x<<"P.Y = "<<p.y;
                    if(abs(p.x-320)<DELTA_EDGE ||  abs(p.x-0)<DELTA_EDGE){
                        x_edge_counter++;

                        circle(output,p,10,Scalar(255,0,0),5);
                    }

                    qDebug()<<"dist 1 = "<<(p.y- MAX_Y);
                    qDebug()<<"dist 2 = "<<(p.y- MIN_Y);
                    if(abs(p.y- MAX_Y)<DELTA_EDGE || abs(p.y-MIN_Y)<DELTA_EDGE){
                        y_edge_counter++;

                        circle(output,p,10,Scalar(255,0,0),5);
                    }

                    if(x_edge_counter >4  || y_edge_counter >4)
                        return false;


                }

                qDebug()<<"X COUTER : "<<x_edge_counter<<" ---- Y COUNTER : "<<y_edge_counter;

                if(x_edge_counter == 4  || y_edge_counter==4

                        || (x_edge_counter == 2  && y_edge_counter==2)
                        || (x_edge_counter == 2  && y_edge_counter==0)){
                    if(color_tag==ColorDetection::RED)
                        red_contour =contours[i];
                    else

                        if(color_tag==ColorDetection::YELLOW)
                            yellow_contour =contours[i];


                    foundEdge =true;
                    qDebug("8 VERTEX and CONVEX");
                    //circle(output,p,3,color,-4);

                    qDebug("Edge DETECTION");
                    imshow("EDGES ",output);
                    return true;
                }

            }
        }
    }
    imshow("EDGES ",output);
    return false;



}

bool UDetection::detectEdges(Mat src)
{
    int x_edge_counter=0,y_edge_counter=0;

    qDebug()<<"IN EDGE DETECTION";
    Mat input =src.clone(),output;
    Mat threshold_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;


    int MAX_Y=240;
    int MIN_Y=0;
    if(croped){
        if(up_down ==0)
            MAX_Y=120;
        else
            MIN_Y=120;
    }

    /// Detect edges using Threshold
    threshold( input, threshold_output, 100, 255, THRESH_BINARY );
    /// Find contours
    findContours( threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

    /// Approximate contours to polygons + get bounding rects and circles
    vector<vector<Point> > contours_poly( contours.size() );
    Scalar color;

    cvtColor(threshold_output,output,CV_GRAY2BGR);
    for( int i = 0; i < contours.size(); i++ )
    {

        approxPolyDP( Mat(contours[i]), contours_poly[i], 8, true );

        // drawContours(output,contours,i,color,3);
        color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );

        int poly_size= contours_poly[i].size();
        qDebug()<<"CONTOUR SIZE"<<poly_size;

        qDebug()<<"contour area : "<<contourArea(contours[i]);
        if(contourArea(contours[i]) > BODY_AREA2
                && (poly_size ==4 || poly_size == 6)){
            //drawContours(output,contours,i,color,5);

            //if( contours_poly[i].size()==4 &&
            for(int l=0; l<contours_poly[i].size();l++){
                Point p=contours_poly[i][l];
                circle(output,p,10,Scalar(255,0,0),5);
                //qDebug()<<" EDGE : P.X = "<<p.x<<"P.Y = "<<p.y;
                imshow("EDGES ",output);
                if(abs(p.x-320)<DELTA_EDGE ||  abs(p.x-0)<DELTA_EDGE){
                    x_edge_counter++;

                    circle(output,p,10,Scalar(255,0,0),5);
                }
                if(abs(p.y-MAX_Y)<DELTA_EDGE || abs(p.y-MIN_Y)<DELTA_EDGE){
                    y_edge_counter++;

                    circle(output,p,10,Scalar(255,0,0),5);
                }

                // qDebug()<<"X COUTER : "<<x_edge_counter<<" ---- Y COUNTER : "<<y_edge_counter;
                if(x_edge_counter == 4  || y_edge_counter==4
                        || (x_edge_counter == 2  && y_edge_counter==2)){

                    qDebug("8 VERTEX and CONVEX");
                    //circle(output,p,3,color,-4);

                    imshow("EDGES ",output);
                    return true;


                }

            }
        }
    }
    return false;
}

int UDetection::calculateLength(Vec4i line)
{
    int x1, x2, y1, y2;
    int distance;
    x1=line[0];
    x2=line[2];
    y1=line[1];
    y2=line[3];

    int distancex = (x2 - x1)^2;
    int distancey = (y2 - y1)^2;

    distance = sqrt(distancex + distancey);
    return distance;
}


bool UDetection::isU(vector<Point> points)
{
    int counter_x=0;
    int counter_y=0;
    bool samePoint_x=false;
    bool samePoint_y=false;
    vector<int> Xs;
    vector<int> Ys;


    vector<int> points_by_x;

    vector<int> points_by_y;


    Point p1,p2;

    for(int i=0; i < points.size() ; i++){
        p1=points[i];
        for(int j=i+1; j < points.size() ; j++){

            p2=points[j];

            samePoint_x=false;
            samePoint_y=false;


            //qDebug()<<"X LENGTH = "<<abs (p1.x - p2.x );

            //qDebug()<<"Y LENGTH = "<<abs (p1.y - p2.y );

            if(abs (p1.x - p2.x )< 15)
            {
                for(int k= 0 ; k< Xs.size() ;k++)
                    if(Xs[k] == i || Xs[k] == j){
                        samePoint_x =true;
                        break;
                    }

                if(!samePoint_x){

                    circle(rgb,p1,15,Scalar(150,25,150),5);

                    circle(rgb,p2,15,Scalar(150,25,150),5);
                    counter_x++;
                    Xs.push_back(i);
                    //points_by_x.push_back(i);
                    Xs.push_back(j);
                }
            }

            else if(abs (p1.y - p2.y )< 21)
            {
                for(int k= 0 ; k< Ys.size() ;k++)
                    if(Ys[k] == i || Ys[k] == j){
                        samePoint_y =true;
                        break;
                    }

                if(!samePoint_y){

                    // color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );

                    circle(rgb,p1,10,Scalar(0,255,255),5);

                    circle(rgb,p2,10,Scalar(0,255,255),5);
                    counter_y++;
                    Ys.push_back(i);
                    //points_by_y.push_back(i);
                    Ys.push_back(j);
                }
            }
        }
    }

    Point center = findCenterPoint(points);

    circle(rgb,center,10,Scalar(0,0,255),5);

    //sort(points_by_x.begin(),points_by_x.end(),myobject);
    qDebug()<<"X COUNTER = "<<counter_x <<"  "<<"Y COUNTER = "<<counter_y;
    if((counter_x ==4 && counter_y ==4)
            || (counter_x ==3 && counter_y ==3)
            || (counter_x ==3 && counter_y ==4)
            || (counter_x ==4 && counter_y ==3))
        return true;
    return false;

}

bool UDetection::findMinLength(vector<Point> points)
{

    /* int minLen = 1000;
    for (int m = 0 ; m < points.size() ; m++)
        for(int n=m+1 ; n<points.size() ; n++)
        {
            if(abs(p-lines[n][3])>maxLen)
                minLen = abs(lines[m][0]-lines[n][3]);
        }
    return maxLen;*/
}

Point UDetection::findCenterPoint(vector<Point> points)
{

    sort(points.begin(),points.end(),myobject);//sorted by X
    int minX=points[0].x;
    int maxX=points[points.size()-1].x;


    sort(points.begin(),points.end(),myobject1);//sorted by Y

    int minY=points[0].y;
    int maxY=points[points.size()-1].y;



    return Point((minX+maxX)/2,(minY+maxY)/2+25);

}


int UDetection::findMaxLength(vector<Vec4i> lines)
{
    int maxLen = 0;
    for (int m = 0 ; m < lines.size() ; m++)
        for(int n=m+1 ; n<lines.size() ; n++)
        {
            if(abs(lines[m][0]-lines[n][3])>maxLen)
                maxLen = abs(lines[m][0]-lines[n][3]);
        }
    return maxLen;
}
