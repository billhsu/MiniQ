package com.tikoLabs.quadcontrol;

import android.content.Context;
import android.graphics.Canvas;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.widget.SeekBar;

public class VerticalSeekbar extends SeekBar {

	 public VerticalSeekbar(Context context) {
	        super(context);
	      
	    }

	    public VerticalSeekbar(Context context, AttributeSet attrs, int defStyle) {
	        super(context, attrs, defStyle);
	    }

	    public VerticalSeekbar(Context context, AttributeSet attrs) {
	        super(context, attrs);
	    }

	    protected void onSizeChanged(int w, int h, int oldw, int oldh) {
	        super.onSizeChanged(h, w, oldh, oldw);
	    }

	    @Override
	    protected synchronized void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
	        super.onMeasure(heightMeasureSpec, widthMeasureSpec);
	       int df= getMeasuredWidth()-getMeasuredHeight();
	        setMeasuredDimension(getMeasuredHeight(), getMeasuredWidth()*Math.abs(df));
	    }

	    protected void onDraw(Canvas c) {
	        c.rotate(-90);
	        c.translate(-getHeight(), 0);
	    
	        super.onDraw(c);
	    }

	    @Override
	    public boolean onTouchEvent(MotionEvent event) {
	        if (!isEnabled()) {
	            return false;
	        }

	        switch (event.getAction()) {
	            case MotionEvent.ACTION_DOWN:
	            case MotionEvent.ACTION_MOVE:
	            case MotionEvent.ACTION_UP:
	                setProgress(getMax() - (int) (getMax() * event.getY() / getHeight()));
	                onSizeChanged(getWidth(), getHeight() , 0, 0);
	                break;

	            case MotionEvent.ACTION_CANCEL:
	                break;
	        }
	        return true;
	    }

		
		public synchronized void setProgressAndThumb(int progress)		
		{
		  
			setProgress(getMax() - (getMax()- progress));
            onSizeChanged(getWidth(), getHeight() , 0, 0);
		}
		public synchronized void setMaximum(int maximum)
		{
			setMax(maximum);
		}
		public synchronized int getMaximum()
		{
			return getMax();
		}
	}