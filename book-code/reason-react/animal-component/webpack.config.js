/***
 * Excerpted from "Web Development with ReasonML",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/reasonml for more book information.
***/
const path = require('path');
const HtmlWebpackPlugin = require('html-webpack-plugin')
const outputDir = path.join(__dirname, 'build/');

const isProd = process.env.NODE_ENV === 'production';

module.exports = {
  entry: './src/Index.bs.js',
  mode: isProd ? 'production' : 'development',
  output: {
    path: outputDir,
    publicPath: outputDir,
    filename: 'Index.js',
  },
  plugins: [
    new HtmlWebpackPlugin({
      template: 'src/index.html',
      inject: false
    })
  ],
  /*
   * Addition to template's webpack.config.js starts here.
  */
  module: {
    rules: [
      {
        /* files ending in .png load into [path][name].[ext]*/
      },
      {
        /* files ending in .css load into [name].[ext]*/
      }
    ]
  },
  /* End addition to template webpack.config.js */
  devServer: {
    compress: true,
    contentBase: outputDir,
    port: process.env.PORT || 8000,
    historyApiFallback: true
  }
};
