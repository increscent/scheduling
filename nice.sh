#!/bin/bash

sudo nice -19 ./spin -l a &
sudo nice -19 ./spin -l b &
sudo nice -19 ./spin -l c &
sudo nice --20 ./spin -l z &
