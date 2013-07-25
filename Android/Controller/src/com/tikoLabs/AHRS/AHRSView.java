// AHRS view for Android
// Bill Hsu (C) 2013
// Nanyang Technological University
// github.com/billhsu
package com.tikoLabs.AHRS;


import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Paint.Style;
import android.graphics.Path;
import android.util.AttributeSet;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.View;

public class AHRSView extends View {
	private float roll=-30.0f,pitch=20.0f,yaw=0.0f;
	
	private final float ang_rad = 3.14159f/180.0f;
	private Paint horizontalLine;
	private Paint ahrsLine;
	private Paint downPoly;
	private Paint upPoly;
	private Paint ptText;
	private float centerX = 0; // Center view x position
	private float centerY = 0; // Center view y position
	private float shortLen = 50;
	private float shortLen_ = 50;
	private float longLen = 125;
	private float longLen_ = 125;
	private float horPara=10.0f;
	private float horPara_=10.0f;
	private float pitchInterval = 20.0f;
	private float pitchInterval_ = 20.0f;
	Path path;
	
	public void setRoll(float _roll){roll=_roll;invalidate();}
	public void setPitch(float _pitch){pitch=-_pitch;invalidate();}
	public void setYaw(float _yaw){roll=_yaw;invalidate();}
	
	@Override
	protected void onDraw(Canvas canvas) {
		super.onDraw(canvas);
		DisplayMetrics metrics = getContext().getResources().getDisplayMetrics();
		centerX = (getWidth()) / 2;
		centerY = (getHeight()) / 2;
		shortLen = shortLen_*centerX/200;
		longLen = longLen_*centerX/200;
		horPara = horPara_*centerX/200;
		pitchInterval = pitchInterval_*centerX/200;
		
		int startIndex = (int) (pitch/10-7);
		int endIndex = (int) (pitch/10+7);
		canvas.save();
		canvas.rotate(roll, centerX, centerY);
		if(startIndex>-18 && endIndex<18){
			path.reset();
			path.moveTo(-100, startIndex*10);
			path.lineTo(centerX*2+100, startIndex*10);
			path.lineTo(centerX*2+100, centerY-pitch*centerX/200*2*metrics.density);
			path.lineTo(-100, centerY-pitch*centerX/200*2*metrics.density);
			path.lineTo(-100, startIndex*10);
			canvas.drawPath(path, upPoly);
			
			path.reset();
			path.moveTo(-100, centerY*2+100);
			path.lineTo(centerX*2+100, centerY*2+100);
			path.lineTo(centerX*2+100, centerY-pitch*centerX/200*2*metrics.density);
			path.lineTo(-100, centerY-pitch*centerX/200*2*metrics.density);
			path.lineTo(-100, centerY*2+100);
			canvas.drawPath(path, downPoly);
		}
		else{
			int i;
			if(startIndex<-18+2) i=-18;
			else i = 18;
			path.reset();
			if(i==18)startIndex-=18;
			path.moveTo(-100, startIndex*10);
			path.lineTo(centerX*2+100, startIndex*10);
			path.lineTo(centerX*2+100, centerY-pitch*centerX/200*2*metrics.density+pitchInterval*i);
			path.lineTo(-100, centerY-pitch*centerX/200*2*metrics.density+pitchInterval*i);
			path.lineTo(-100, startIndex*10);
			canvas.drawPath(path, downPoly);
			
			path.reset();
			path.moveTo(-100, centerY*2+100);
			path.lineTo(centerX*2+100, centerY*2+100);
			path.lineTo(centerX*2+100, centerY-pitch*centerX/200*2*metrics.density+pitchInterval*i);
			path.lineTo(-100, centerY-pitch*centerX/200*2*metrics.density+pitchInterval*i);
			path.lineTo(-100, centerY*2+100);
			canvas.drawPath(path, upPoly);
		}

		Log.i("AHRS","start:"+startIndex+" end:"+endIndex);

		// draw ahrs line
		for(int i=startIndex; i<endIndex; ++i)
		{
			drawAHRSLine(canvas, (float)(centerY-pitch*centerX/200*2*metrics.density + (pitchInterval)*i), (i%2==0), i);
		}
		canvas.restore();
		// draw center horizontal line 
		canvas.drawLine(centerX, centerY, centerX-horPara, centerY+horPara, horizontalLine);
		canvas.drawLine(centerX, centerY, centerX+horPara, centerY+horPara, horizontalLine);
		canvas.drawLine(centerX-horPara, centerY+horPara, centerX-horPara*2, centerY, horizontalLine);
		canvas.drawLine(centerX+horPara, centerY+horPara, centerX+horPara*2, centerY, horizontalLine);
		canvas.drawLine(centerX-horPara*2, centerY, centerX-horPara*4, centerY, horizontalLine);
		canvas.drawLine(centerX+horPara*2, centerY, centerX+horPara*4, centerY, horizontalLine);
	}
	private void drawAHRSLine(Canvas canvas, float yPos, boolean bLong, int i)
	{
		float leng = shortLen;
		if(bLong) leng = longLen;
		leng /= 2.0f;
		
		if (i>18)  {i -= 18*(i/18);}
		if (i<-18) i += 18*(i/-18);
		
		if(i==0 || Math.abs(i)==18) leng = longLen*4;
		float x1,x2,y1,y2;
		x1 = centerX+leng;
		x2 = centerX-leng;
		y1 = yPos;
		y2 = yPos;
		canvas.drawLine(x1, y1, x2, y2, ahrsLine);
		
		x1 += 5;
		
		x2 -= ptText.measureText(""+(-i)*10)+5;

		canvas.drawText(""+(-i)*10, x1, y1, ptText);
		canvas.drawText(""+(-i)*10, x2, y2, ptText);
	}
	

	public AHRSView(Context context) {
		super(context);
	}

	public AHRSView(Context context, AttributeSet attrs) {
		super(context, attrs);
		initAHRSView();
	}

	public AHRSView(Context context, AttributeSet attrs, int defaultStyle) {
		super(context, attrs, defaultStyle);
		initAHRSView();
	}
	
	@Override
	protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
		// setting the measured values to resize the view to a certain width and
		// height
		setMeasuredDimension(measure(widthMeasureSpec), measure(heightMeasureSpec));

		// before measure, get the center of view
		centerX = (int) getWidth() / 2;
		centerY = (int) getWidth() / 2;
	}

	private int measure(int measureSpec) {
		int result = 0;

		// Decode the measurement specifications.
		int specMode = MeasureSpec.getMode(measureSpec);
		int specSize = MeasureSpec.getSize(measureSpec);

		if (specMode == MeasureSpec.UNSPECIFIED) {
			// Return a default size of 200 if no bounds are specified.
			result = 200;
		} else {
			// As you want to fill the available space
			// always return the full available bounds.
			result = specSize;
		}
		return result;
	}

	protected void initAHRSView() {
		DisplayMetrics metrics = getContext().getResources().getDisplayMetrics();
		shortLen_ = metrics.density * shortLen;
		longLen_ = metrics.density * longLen;
		horPara_ = metrics.density * horPara;
		pitchInterval_ = metrics.density * pitchInterval;
		
		horizontalLine = new Paint(Paint.ANTI_ALIAS_FLAG);
		horizontalLine.setStrokeWidth(5);
		horizontalLine.setColor(Color.parseColor("#E0D51B"));
		
		ahrsLine = new Paint(Paint.ANTI_ALIAS_FLAG);
		ahrsLine.setStrokeWidth(6);
		ahrsLine.setColor(Color.WHITE);
		
		upPoly = new Paint(Paint.ANTI_ALIAS_FLAG);
		upPoly.setColor(Color.parseColor("#0166D8"));
		upPoly.setStyle(Style.FILL);
		
		downPoly = new Paint(Paint.ANTI_ALIAS_FLAG);
		downPoly.setColor(Color.parseColor("#AA3E17"));
		downPoly.setStyle(Style.FILL);
		
		path = new Path();
		
		ptText = new Paint(Paint.ANTI_ALIAS_FLAG);
		ptText.setColor(Color.WHITE);
		ptText.setTextSize(20);
	}

}
