/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class name here>
 *-----------------------------------------------------------------------------
 * Exercise Number: #exercise_number#
 * File:			bst.cpp
 * Author(s):		Peter Bauer
 * Due Date:		May 31, 2017
 *-----------------------------------------------------------------------------
 * Description:
 * <your description here>
 *-----------------------------------------------------------------------------
*/
#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
#include "general.h"

struct Node{
  int data;
  Bst right;
  Bst left;
};
Bst new_bst(){
  Bst bst = 0;
  return bst;
}
void delete_bst(Bst bst){
  if (bst == 0) {
    return;
  }
  delete_bst(bst->left);
  delete_bst(bst->right);

  sfree(bst);

}
int get_depth (Bst bst){
  if (bst == 0) {
      return 0;
  }
  int depth_left = get_depth(bst->left) + 1;
  int depth_right = get_depth(bst->right) + 1;

  if (depth_left > depth_right) {
    return depth_left;
  }
  else{
    return depth_right;
  }

}
void add (Bst *bst, int value){
  Bst &root = *bst;
  if (root == 0) {
    root = (Bst)malloc(sizeof(struct Node));
    root->data = value;
    root->left = 0;
    root->right = 0;
  }
  else if (value <= root->data) {
    add(&root->left, value);
  }
  else if (value > root->data) {
    add(&root->right, value);
  }
}
int root_value (Bst bst){
  if (bst != 0) {
    return bst->data;
  }
  return 0;
}
Bst left_subtree (Bst root){
  if (root == 0) {
    return 0;
  }
  return root->left;
}
Bst right_subtree (Bst root){
  if (root == 0) {
    return 0;
  }
  return root->right;
}
int traverse_pre_order (Bst bst, int *elements, int start){
  if (bst != 0) {
    elements[start] = bst->data;
    start++;
    start = traverse_pre_order(left_subtree(bst), elements, start);
    start = traverse_pre_order(right_subtree(bst),elements, start);
  }
  return start;
}
int traverse_in_order (Bst bst, int *elements, int start){
  if (bst != 0) {
    start = traverse_in_order(left_subtree(bst), elements, start);
    elements[start] = bst->data;
    start++;
    start = traverse_in_order(right_subtree(bst), elements, start);
  }
  return start;
}
int traverse_post_order (Bst bst, int *elements, int start){
  if (bst != 0) {
    start = traverse_post_order(left_subtree(bst), elements, start);
    start = traverse_post_order(right_subtree(bst), elements, start);
    elements[start] = bst->data;
    start++;
  }
  return start;
}
bool are_equal (Bst bst1, Bst bst2){
  if(bst1 == 0 && bst2 == 0)return true;
  if(bst1 == bst2)return true;

  int arr1[75];
  int arr2[75];
  int len1 = traverse_in_order(bst1, arr1, 0);
  int len2 = traverse_in_order(bst2, arr2, 0);
  if(len1 != len2)return false;
  for (int i = 0; i < len1; i++) {
    if (arr1[i] != arr2[i])return false;
  }
  return true;
}
void most_left_longest_branch (Bst bst, Bst *branch){
  if(bst == 0)return;
  add(branch, bst->data);
  if (get_depth(bst->left) >= get_depth(bst->right)) {
    most_left_longest_branch(bst->left, branch);
  }
  else most_left_longest_branch(bst->right, branch);
}
int get_number_of_subtrees (Bst bst){
  if (bst == 0) {
    return -1;
  }
  return get_number_of_subtrees(bst->left) + 1 + get_number_of_subtrees(bst->right) + 1;
}
