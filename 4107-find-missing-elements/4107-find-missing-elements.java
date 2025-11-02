class Solution {
    public List<Integer> findMissingElements(int[] nums) {
        List<Integer> missing = new ArrayList<>();
        Arrays.sort(nums);
        int start = nums[0];
        int end = nums[nums.length - 1];
        Set<Integer> set = new HashSet<>();
        for (int num : nums) {
            set.add(num);
        }

        for (int i = start; i <= end; i++) {
            if (!set.contains(i)) {
                missing.add(i);
            }
        }
        return missing;
    }
}
