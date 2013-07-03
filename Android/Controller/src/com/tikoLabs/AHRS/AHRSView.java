package com.tikoLabs.AHRS;

import android.content.Context;
import android.content.res.TypedArray;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Paint.Style;
import android.util.AttributeSet;
import android.view.View;
import android.view.View.MeasureSpec;

public class AHRSView extends View {
	private Paint horizontalLine;
	private float centerX = 0; // Center view x position
	private float centerY = 0; // Center view y position
	
	@Override
	protected void onDraw(Canvas canvas) {
		// TODO Auto-generated method stub
		super.onDraw(canvas);
		centerX = (getWidth()) / 2;
		centerY = (getHeight()) / 2;
		canvas.drawLine(centerX, centerY, 0, 0, horizontalLine);

	}
	private static float roll=0.0f,pitch=0.0f,yaw=0.0f;

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
		horizontalLine = new Paint();
		horizontalLine.setStrokeWidth(2);
		horizontalLine.setColor(Color.GREEN);
	}
	
	public static void setRoll(float _roll){roll=_roll;}
	public static void setPitch(float _pitch){pitch=_pitch;}
	public static void setYaw(float _yaw){roll=_yaw;}

}
