/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }
 * }
 */
public class Solution {
    TreeNode lca;
    public TreeNode lowestCommonAncestor(TreeNode root, TreeNode p, TreeNode q) {
        dfs(root, p, q);
        return lca;
    }

    private boolean dfs(TreeNode node, TreeNode p, TreeNode q) {
        // Base case: a null node is neither 'p' nor 'q'.
        if (node == null) { return false; }
        // 1.If current node itself is p or q
        int nodeIsPOrQ = (node == p || node == q) ? 1 : 0;
        // 2.Recursively determine if the left and right subtrees contain 'p' or 'q'.
        int leftContainsPOrQ = dfs(node.left, p, q) ? 1 : 0;
        int rightContainsPOrQ = dfs(node.right, p, q) ? 1 : 0;
        // If two of the above three variables are true, the current node is the LCA.
        if (nodeIsPOrQ + leftContainsPOrQ + rightContainsPOrQ == 2) {
            lca = node;
        }
        // Return true if the current subtree contains 'p' or 'q'.
        return nodeIsPOrQ + leftContainsPOrQ + rightContainsPOrQ > 0;
    }
}