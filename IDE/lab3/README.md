# Screenshots
![Main Screen](screenshots/main.png)
![Statistics Screen](screenshots/statistics.png)

# Features
1. 25 minutes pomodoro with possibility to start/stop(reset)
2. Circular progress bar with animation. Used Bounce Interpolator.
3. Vibration on done
4. Saving all results in database
5. Pretty print of results

# Used in project
1. Android Data Binding (MVVM)
2. Android Support Library (Recycler View)
3. SugarORM (ORM)
4. Pretty Time

# Conclusion
In this laboratory work I created a simple "Pomodoro App". To implement this task, I decided to use a Custom View because Android doesn't have a circular progress bar. I decided to go with newest Android tools like Android Data Biding(with this feature we can build and MVVM Architecture) and Recycler View that is an analogy of ListView but more features and more customizable. For storing data in SQLite I chosen SugarORM which is a very simple ORM Android library. For displaying time in a cool format I found library called "Pretty Time" which can be very useful for pretty printing time. 
