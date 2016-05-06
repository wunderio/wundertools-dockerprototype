// Require Node Modules
var gulp          = require('gulp'),
    filter        = require('gulp-filter'),
    uglify        = require('gulp-uglify'),
    concat        = require('gulp-concat'),
    ext           = require('gulp-ext-replace'),
    nodesass      = require('node-sass'),
    sass          = require('gulp-sass'),
    globbing      = require('gulp-css-globbing'),
    postcss       = require('gulp-postcss');
    autoprefixer  = require('gulp-autoprefixer'),
    minifycss     = require('gulp-minify-css'),
    sourcemaps    = require('gulp-sourcemaps'),
    livereload    = require( 'gulp-livereload' ),
    injectReload  = require('gulp-inject-reload');

// Confingure our directories
    var paths = {
      js:     'js/**/*.js',
      css:    'source/css',
      sass:   'source/sass',
      img:    'source/img',
    };

// Sass Tasks
gulp.task('style', function() {
  return gulp.src([paths.sass + '/**/*.scss'])
    .pipe(globbing({ extensions: ['.scss'] }))
    .pipe(sourcemaps.init())
    .pipe(sass({includePaths: ['./node_modules/breakpoint-sass/stylesheets', './node_modules/singularitygs/stylesheets']}))
    .pipe(sourcemaps.write('.'))
    .pipe(gulp.dest(paths.css))
    .pipe(injectReload())
    .pipe(livereload());
});

gulp.task('production', function() {
  return gulp.src([paths.sass + '/**/*.scss'])
    .pipe(globbing({ extensions: ['.scss'] }))
    .pipe(sass({includePaths: ['./node_modules/breakpoint-sass/stylesheets', './node_modules/singularitygs/stylesheets']}))
    .pipe(gulp.dest(paths.css))
});

// Watch for changes
gulp.task('watch', function(){
  livereload.listen();
  gulp.watch(paths.sass + '/**/*', ['style'])
})

// Run watch and wait for changes
gulp.task('default', ['watch'])
